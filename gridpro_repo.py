import subprocess
import os
import sys

class gridpro_compile:
    repos = {}
    root_directory = ""
    def git(self,args, arg2 = ''):
        print("gp:\\> Executing :", ' '.join(args), " ", ' '.join(arg2),  sep = "")
#       return subprocess.run(['git'] + args, cwd = self.working_directory)
        cmd = ['git'] + args
        cmd = ' '.join(cmd)
        if(args[0] == 'clone'):
            print("please wait ")
            ps = subprocess.Popen(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT, cwd = self.root_directory)
        else:
            ps = subprocess.Popen(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT, cwd = self.working_directory)
        output = ps.communicate()[0]
        output = output.decode();
        output = output.split('\n');
        txt = "";
        f = open("checkout_Log.txt",'a')
        f.writelines(arg2 +'\n');
        f.writelines('---------------------------------\n')
        for out in output:
            
            f.writelines(out+'\n');
            if(out.strip()!=""):
                print('gp: ', out)
            if(out.startswith('M\t')):
                pass
            else:
                txt = txt + out;
        f.close();
                

    def setPath(self, s):
        self.root_directory = s;
        self.working_directory = s + "/GridPro_WS";
    def cl(self,args):

        return subprocess.run(['cl'] + args, cwd = self.working_directory)
    def cd(self,args):
        if args == '..':
            ix = self.working_directory.rfind("/")
            self.working_directory = self.working_directory[0:ix]
        if args == '~':
            
            self.working_directory = self.root_directory
        else:
            self.working_directory = self.working_directory + "/" + args
        #print("Working Directory", self.working_directory)
    def __init__(self):
        self.working_directory = os.getcwd()
def readBranches(gc):
    f = open(gc.root_directory + "/branches.txt",'r');
    txt = f.read();
    gc.repos = {}
    txt = txt.split('\n');
    print(txt);
    for line in txt:
        if(line.strip() ==""): continue;
        words = line.split(" ");

        gc.repos[words[0]] = words[1]

def clone_repo(gc):
    
    gc.git(['clone', 'git@github.com:gridpro/GridPro_WS.git',  '--recurse-submodules'])
    gc.cd('GridPro_WS')

    readBranches(gc);
    for key in gc.repos.keys():
        gc.cd("~");
        gc.cd(key)
        gc.git(['checkout', gc.repos[key]],key)

   

def checkout_all(gc):
    f = open("checkout_log.txt",'w')
    f.close()
    

    readBranches(gc);
    for key in gc.repos.keys():
        print('\nChecking ', key);
        print("-------------------------------");
        gc.cd("~");
        gc.cd(key)
        gc.git(['checkout', gc.repos[key]],key)
        #gc.git(['checkout'],key)

def pull_all(gc):
    f = open("checkout_Log.txt",'w')
    f.close()
    readBranches(gc);
    for key in gc.repos.keys():
        print('\nChecking ', key);
        print("-------------------------------");
        gc.cd("~");
        gc.cd(key)
        gc.git(['pull'],key)

if __name__ == '__main__':
    n = len(sys.argv);
    args = sys.argv
    gc = gridpro_compile()
    gc.setPath(os.getcwd())
    if n>1:
        if args[1] == 'checkout':
            checkout_all(gc);
        if args[1] == 'pull':
            pull_all(gc);

        if args[1] == 'clone':
            clone_repo(gc);

        if args[1] == 'branch':
            readBranches(gc);
            for key in gc.repos.keys():
                print(key,': ', gc.repos[key])
#remotes/origin/V8.1.Enhancements
