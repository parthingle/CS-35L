#!/usr/bin/python

import random, sys, locale, string
from optparse import OptionParser

"""To set all the categories of the global locale"""
locale.setlocale(locale.LC_ALL, '')

class comm:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def getList(self):
        line_list=list(self.lines)
        return line_list

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Output at most 3 columns of unique or matching lines between the files"""
    
    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1", action="store_true",dest="suppresscol1",
                      help="suppress lines unique to Alpha",
                      default=False)
    parser.add_option("-2", action="store_true",dest="suppresscol2",
                      help="suppress lines unique to Beta",
                      default=False)
    parser.add_option("-3", action="store_true",dest="suppresscol3",
                      help="suppress lines common to both files",
                      default=False)
    parser.add_option("-u", action="store_true",dest="sortUnsorted",
                      help="sort unsorted files before comparing",
                      default=False)

    options, args = parser.parse_args(sys.argv[1:])

    if len(args)<2:
        parser.error("Missing operand")
    elif len(args)>2:
        parser.error("Too many operands")

    input1 = args[0]
    input2 = args[1]
    
    try:
        if input1=="-":
            alpha=list(sys.stdin.readlines())
        else:
            lines1=comm(input1)
            alpha=list(lines1.getList())

        if input2=="-":
            beta=list(sys.stdin.readlines())
        else:
            lines2=comm(input2)
            beta=list(lines2.getList())
    except:
        parser.error("Input should be text files.")

    if options.sortUnsorted==False:
        if alpha!= sorted(alpha) and beta!=sorted(beta):
            parser.error("Both input are unsorted.")
        elif alpha!=sorted(alpha):
            parser.error("FILE1 is unsorted.")
        elif beta!=sorted(beta):
            parser.error("FILE2 is unsorted.")

    # This function set option flags
    def flag(str, col):
        if col==1:
            if options.suppresscol1==True:
                return
        elif col==2:
            if options.suppresscol2==True:
                return
            if options.suppresscol1==False:
                sys.stdout.write("\t")
        elif col==3:
            if options.suppresscol3==True:
                return
            if options.suppresscol1==False:
                sys.stdout.write("\t")
            if options.suppresscol2==False:
                sys.stdout.write("\t")

        sys.stdout.write(str)  

    #sort both files before comparation
    alpha.sort()
    beta.sort()

    dictAlpha={}
    dictBeta={}

    
    for line in alpha:
        if line in dictAlpha:
            dictAlpha[line]+=1
        else:
            dictAlpha[line]=1
    for line in beta:
        if line in dictBeta:
            dictBeta[line]+=1
        else:
            dictBeta[line]=1

    #set() removes repeated lines
    uniqueAlpha=list(set(alpha))
    uniqueBeta=list(set(beta))

    # sort FILE1 and FILE2 after removing repeated lines
    uniqueAlpha.sort()
    uniqueBeta.sort()

    # check whether the lines in FILE1 is also in FILE2
    for line in uniqueAlpha:
        c1=1
        c3=0
        if line in dictBeta:
            c1= max(0,dictAlpha[line]-dictBeta[line])
            c3= min(dictAlpha[line],dictBeta[line])
        else:
            c1=dictAlpha[line]
        while (c1>0):
            flag(line,1)
            c1-=1
        while (c3>0):
            flag(line,3)
            c3-=1
            
    # check whether the lines in FILE2 is also in FILE1
    for line in uniqueBeta:
        c2=0
        if line in dictAlpha:
            c2= max(0,dictBeta[line]-dictAlpha[line])
        else:
            c2=dictBeta[line]
        while (c2>0):
            flag(line,2)
            c2-=1
            
if __name__ == "__main__":
    main()
