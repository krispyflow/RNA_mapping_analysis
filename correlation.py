from ctypes.wintypes import LPWIN32_FIND_DATAA
from scipy.stats import pearsonr
import os

path1 = "/Users/apple/Downloads/Das Lab/Data/Analysis/dec 22-jan 23/T2_V1_reactivity/reactivity_intron"
path2 = "/Users/apple/Downloads/Das Lab/Data/Analysis/dec 22-jan 23/T2_V1_reactivity/v1_reactivities"
path3 = "/Users/apple/Downloads/Das Lab/Data/Analysis/dec 22-jan 23/T2_V1_reactivity/T2_reactivities"
path4 = "/Users/apple/Downloads/Das Lab/Data/Analysis/dec 22-jan 23/T2_V1_reactivity/corr"
ignore1 = "Coverage"
ignore2 = "nan"

def cov_check(file_name):
    lc = file_name.readline()
    lc = lc.strip('\n')
    lin = lc.split(' ')
    num = float(lin[-1])
    if num < 1971:
       return 0


def get_corr2(ref, test):
    a_ref, a_test = [], []
    for l1, l2, in zip (ref, test):
        l1 = ref.readline()
        l2 = test.readline()
        if (ignore1 in l1) or (ignore2 in l1) or (l1 == ""):
            pass
        elif (ignore1 not in l2) and (ignore2 not in l2) and (l2 != ""):
            a_ref.append(float(l1))
            a_test.append(float(l2))
        else:
            pass
    
    corr2 = pearsonr(a_ref, a_test)
    return corr2  

def get_corr3(rr, v1, t2):
    a_rv, a_rt, a_v1, a_t2= [], [], [], []
    for l1, l2, l3 in zip(rr, v1, t2):
        l1 = rr.readline()
        l2 = v1.readline()
        l3 = t2.readline()
        if (ignore1 in l1) or (ignore2 in l1) or (l1 == ""):
            pass
        elif (ignore1 not in l2) and (ignore2 not in l2) and (l2 != ""):
            a_rv.append(float(l1))
            a_v1.append(float(l2))
            if (ignore1 not in l3) and (ignore2 not in l3) and (l3 != ""):
                a_rt.append(float(l1))
                a_t2.append(float(l3))
        else:
            pass
    print("RV:", a_rv)
    print("RT:", a_rt)
    print("V1:", a_v1)
    print("T2:", a_t2)
    corr_v1 = pearsonr(a_rv, a_v1)
    corr_t2 = pearsonr(a_rt, a_t2)
    return corr_v1, corr_t2

os.chdir(path4)    
w_v1 = open("corr_v1.txt", 'w')
w_t2 = open("corr_t2.txt", 'w')

for f1, f2, f3 in zip(os.listdir(path1),os.listdir(path2),os.listdir(path3)):
    os.chdir(path1)
    rr = open(f1, 'r')
    c1 = cov_check(rr)

    os.chdir(path2)
    v1 = open(f2, 'r')
    c2 = cov_check(v1)

    os.chdir(path3)
    t2 = open(f3, 'r')
    c3 = cov_check(t2)
    
    if (c1 == 0):
        rr.close()
        v1.close()
        t2.close()
    elif (c2 == 0) and (c3 != 0):
        x = get_corr2(rr, t2)
        os. chdir(path4)
        w_t2.write('%s %s' % (str(x), '\n'))
    elif (c2 != 0) and (c3 == 0):
        y = get_corr2(rr, v1)
        os. chdir(path4)
        w_t2.write('%s %s' % (str(y), '\n'))  
    elif (c2 == 0) and (c3 == 0):
        rr.close()
        v1.close()
        t2.close()
    else:    
        a, b = get_corr3(rr, v1, t2)
        os.chdir(path4)

        w_v1.write('%s %s' % (str(a), '\n'))
        w_t2.write('%s %s' % (str(b), '\n'))
        rr.close()
        v1.close()
        t2.close()
w_v1.close()
w_t2.close()