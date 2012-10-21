// UVa10966 3KP-Bash Project
// Rujia Liu
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cstring>
using namespace std;

typedef unsigned long long LL;
typedef vector<int> VI;
typedef vector<string> VS;

const string ERROR_BAD_USAGE = "bad usage\n";
const string ERROR_NO_COMMAND = "no such command\n";
const string ERROR_DIR_NOT_FOUND = "path not found\n";
const string ERROR_DIR_FOUND = "a directory with the same name exists\n";
const string ERROR_DIR_OR_FILE_FOUND = "file or directory with the same name exists\n";
const string ERROR_FILE_NOT_FOUND = "file not found\n";
const string ERROR_EMPTY = "[empty]\n";

// if delim != ' ', make sure that no space characters exist in s
VS split(string s, char delim=' ') {
  if(delim != ' ')
    for(int i = 0; i < s.length(); i++) if(s[i] == delim) s[i] = ' ';
  stringstream ss(s);
  VS ret;
  string x;
  while(ss >> x) ret.push_back(x);
  return ret;
}

// return 1 if success, 0 if on error
int get_int(string s, LL& v) {
  stringstream ss(s);
  if(ss >> v) return 1;
  return 0;
}

string trim(string s) {
  int L, R;
  for(L = 0; L < s.length(); L++) if(!isspace(s[L])) break;
  for(R = s.length()-1; R > L; R--) if(!isspace(s[R])) break;
  return s.substr(L, R-L+1);
}

struct File {
  int parent;
  string name;
  string fullpath; // cached fullpath name
  LL size;
  bool dir;
  bool hidden;
  vector<int> subdir;
  File(int parent=0, string name="", LL size=0, bool dir=true, bool hidden=false):parent(parent),name(name),size(size),dir(dir),hidden(hidden) {}
};

vector<File> fs;
int curDir;

// lexicograhically smaller
bool comp(const int& x, const int& y) {
  return fs[x].fullpath < fs[y].fullpath;
}

// compare size first (increasing)
bool comps(const int& x, const int& y) {
  return fs[x].size < fs[y].size || (fs[x].size == fs[y].size && fs[x].fullpath < fs[y].fullpath);
}

// compare size first (decreasing)
bool compS(const int& x, const int& y) {
  return fs[x].size > fs[y].size || (fs[x].size == fs[y].size && fs[x].fullpath < fs[y].fullpath);
}

// return the node number. -1 on error
int findFileInDirectory(int node, string name) {
  VI& subdir = fs[node].subdir;
  for(int i = 0; i < subdir.size(); i++)
    if(fs[subdir[i]].name == name) return subdir[i];
  return -1;
}

// if the end of path is '/', remove it first
string joinPath(string path, string name) {
  if(path[path.size()-1] != '/') path += "/";
  return path + name;
}

// get the absolute path string for a node
string getAbsolutePath(int node) {
  if(!node) return "/";
  return joinPath(getAbsolutePath(fs[node].parent), fs[node].name);
}

// create a file (regular/directory) in a node (the caller should ensure that the node represents a directory)
int createFileInDirectory(int node, string name, LL size, bool dir, bool hidden) {
  fs.push_back(File(node, name, size, dir, hidden));
  int x = fs.size()-1;  
  fs[x].fullpath = joinPath(getAbsolutePath(node), name);
  fs[node].subdir.push_back(x);
  return x;
}

// return the node of a path (could be relative path or absolute path). return -1 on error
int getDirNode(string path) {
  if(!path.length()) return curDir;
  int node = curDir; // relative path by default
  if(path[0] == '/') node = 0; // absolute path
  VS dirs = split(path, '/');
  for(int i = 0; i < dirs.size(); i++) {
    if(dirs[i] == ".") continue;
    else if(dirs[i] == "..") {
      if(!node) return -1; // root has no parent
      node = fs[node].parent;
    } else {
      int x = findFileInDirectory(node, dirs[i]);
      if(x == -1 || !fs[x].dir) return -1; // cannot enter a regular file
      node = x;
    }
  }
  return node;
}

// check if the filename is valid
int isValidFileName(string name) {
  if(name.length() == 0 || name.length() > 255) return 0;
  if(name == "." || name.find("..") != string::npos) return 0;
  for(int i = 0; i < name.length(); i++)
    if(!isdigit(name[i]) && !isalpha(name[i]) && name[i] != '.') return 0;
  return 1;
}

// split a fullpath into a directory part and a filename part
// return the node of the directory part. return -1 if path not found
int splitFileName(string fullpath, string& filename) {
  int n = fullpath.length();
  int x = n;
  for(int i = fullpath.length()-1; i >= 0; i--) {
    if(fullpath[i] == '/') { // the last '/'
      filename = fullpath.substr(i+1);
	  string dir = fullpath.substr(0, i);
	  if(dir == "") return 0; // relative to root, NOT current directory
      return getDirNode(dir);
    }
  }
  filename = fullpath;
  return curDir;
}

// new BASH session
void newSession() { fs.clear(); fs.push_back(File()); curDir = 0; }

// Given the filename, find all matching files in a node, possibly recursively. Append the items in "out", which is a vector of nodes
// if filename == "", we simply list the files
void findFileEx(VI& out, int node, string filename, bool recur, bool hidden, bool f=true, bool d=true) {
  VI& subdir = fs[node].subdir;
  for(int i = 0; i < subdir.size(); i++) {
    int x = subdir[i];
    if(fs[x].dir && recur) findFileEx(out, x, filename, recur, hidden, f, d);
    if(fs[x].hidden && !hidden) continue;
    if(filename == "" || fs[x].name == filename) {
      if((fs[x].dir && d) || (!fs[x].dir && f)) out.push_back(x);
    }
  }
}

// format the file list
string formatFiles(const VI& out) {
  stringstream ss;
  for(int i = 0; i < out.size(); i++) {
    ss << fs[out[i]].fullpath << " " << fs[out[i]].size;
    if(fs[out[i]].hidden) ss << " " << "hidden";
    if(fs[out[i]].dir) ss << " " << "dir";
    ss << "\n";
  }
  return ss.str();
}

// get arguments and switches
bool parseArgs(VS params, VS& args, bool* sw, LL &v) {
  LL v2;
  for(int i = 0; i < params.size(); i++)
    if(params[i][0] == '-') {
      if(isalpha(params[i][1])) sw[params[i][1]] = 1;
	  else if(get_int(params[i].substr(1), v2)) v = v2; // if there are more than one, only the last one is used
	  else return false;
	}
    else args.push_back(params[i]); // regular arguments (without prefix '-')
  return true;
}

// run a command (except grep) without piping, returns the standard output
string runCommand(const VS& cmd) {
  VS params(cmd.begin()+1, cmd.end()), args;
  bool sw[256];
  LL v = 0;
  memset(sw, 0, sizeof(sw));
  if(!parseArgs(params, args, sw, v)) return ERROR_BAD_USAGE;
  
  int node;
  string filename;
  if(cmd[0] == "cd") {
    if(args.size() != 1) return ERROR_BAD_USAGE;
    if((node = getDirNode(args[0])) == -1) return ERROR_DIR_NOT_FOUND;
    curDir = node;
    return "";
  } else if(cmd[0] == "touch") {
    if(args.size() != 1) return ERROR_BAD_USAGE;
    if((node = splitFileName(args[0], filename)) == -1) return ERROR_DIR_NOT_FOUND;
    if(!isValidFileName(filename)) return ERROR_BAD_USAGE; //!

    int x = findFileInDirectory(node, filename);
    if(x != -1 && fs[x].dir) return ERROR_DIR_FOUND;
    if(x == -1) createFileInDirectory(node, filename, v, false, sw['h']);
    else { fs[x].size = v; fs[x].hidden = sw['h']; }
    return "";
  }
  if(cmd[0] == "mkdir") {
    if(args.size() != 1) return ERROR_BAD_USAGE;
    if((node = splitFileName(args[0], filename)) == -1) return ERROR_DIR_NOT_FOUND;
    if(!isValidFileName(filename)) return ERROR_BAD_USAGE; //!

    int x = findFileInDirectory(node, filename);
    if(x != -1) return ERROR_DIR_OR_FILE_FOUND;
    createFileInDirectory(node, filename, 0, true, sw['h']);
    return "";
  }
  if(cmd[0] == "find") {
    if(args.size() != 1) return ERROR_BAD_USAGE;
    if((node = splitFileName(args[0], filename)) == -1) return ERROR_DIR_NOT_FOUND;
	
    VI out;
    findFileEx(out, node, filename, sw['r'], sw['h']);
    if(out.size() == 0) return ERROR_FILE_NOT_FOUND;
    sort(out.begin(), out.end(), comp);
    return formatFiles(out);
  }
  if(cmd[0] == "ls") {
    if(args.size() > 1) return ERROR_BAD_USAGE;
	node = curDir;
	if(args.size() == 1) if((node = getDirNode(args[0])) == -1) return ERROR_DIR_NOT_FOUND;
	
    VI out;
    findFileEx(out, node, "", sw['r'], sw['h'], !sw['d'], !sw['f']); // ignore bad usage "-d -f"
    if(out.size() == 0) return ERROR_EMPTY;
    if(sw['s']) sort(out.begin(), out.end(), comps);
    else if(sw['S']) sort(out.begin(), out.end(), compS); // ignore bad usage "-s -S"
    else sort(out.begin(), out.end(), comp);
    return formatFiles(out);
  }
  if(cmd[0] == "pwd") {
    if(args.size() != 0) return ERROR_BAD_USAGE;
    return getAbsolutePath(curDir) + "\n";
  }
  if(cmd[0] == "exit") {
    if(args.size() != 0) return ERROR_BAD_USAGE;
    newSession();
    return "";
  }
  if(cmd[0] == "grep") return ERROR_BAD_USAGE;
  return ERROR_NO_COMMAND;
}

// run a commandline (pipes are possible)
string runCommandLine(string cmd) {
  // split commands
  int n = cmd.length();
  int start = 0, inq = 0;
  VS commands;
  for(int i = 0; i <= n; i++)
    if(i == n || (cmd[i] == '|' && !inq))  { commands.push_back(cmd.substr(start, i-start)); start = i+1; }
    else if(cmd[i] == '"') inq = !inq;
  if(!commands.size()) return "";

  // run the first command
  string lastoutput = runCommand(split(commands[0]));
  string line, s, ret;
  // chain the greps after that
  for(int i = 1; i < commands.size(); i++) {
    stringstream ss(commands[i]);
	if(!(ss >> s) || s != "grep") return ERROR_BAD_USAGE;
	getline(ss, s);
	s = trim(s);
	if(s.length() < 2 || s[0] != '"' || s[s.length()-1] != '"') return ERROR_BAD_USAGE;
	s = s.substr(1, s.length()-2); // get the string to be searched for
	
	stringstream input(lastoutput);
	ret = "";
    while(getline(input, line)) {
      if(line.find(s) != string::npos) ret += line + "\n";
	}
	lastoutput = ret;
  }
  return lastoutput;
}

int main() {
  string cmd;
  newSession();
  while(getline(cin, cmd)) {
    cout << runCommandLine(cmd);
  }
  return 0;
}
