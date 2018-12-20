import sys
import codecs

def main():
    if len(sys.argv) < 3:
        print("Usage: python3 fc [filename 1] [filename 2] --show-diff-kinds=all(optional)")
        return
    
    src_fname = sys.argv[1]
    dst_fname = sys.argv[2]
    show_all = False

    if len(sys.argv) > 3:
        if sys.argv[3] == "--show-diff-kinds=all":
            show_all = True
            
    fp_s = open(src_fname, "r", encoding="utf-8")
    fp_d = open(dst_fname, "r", encoding="utf-8")
    ln = 0

    while 1:
        ln += 1
        s_str = fp_s.readline()
        d_str = fp_d.readline()
        if ((s_str == "") and (d_str == "")):
            break
        if ((s_str != "") and (d_str == "")):
            print(" %s has extra lines since line %d" %(src_fname, ln))
            if show_all:
                while s_str != "":
                    print(s_str[:-1])
                    s_str = fp_s.readline()
            break
        if ((s_str == "") and (d_str != "")):
            print("%s has extra lines since line %d" %(dst_fname, ln))
            if show_all:
                while d_str != "":
                    print(d_dtr[:-1])
                    d_str = fp_d.readline()

            break
        s_str = s_str[:-1]
        d_str = d_str[:-1]

        if (s_str != d_str):
            if not show_all:
                print("Line %d is different." %ln)
            else:
                print("Line %d is different. %s expects %s, but %s has %s." %(ln, src_fname, s_str, dst_fname, d_str))

    fp_s.close()
    fp_d.close()

if __name__ == "__main__":
    main()
