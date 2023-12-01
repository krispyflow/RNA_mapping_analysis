from scipy import stats
from matplotlib import pyplot as plt
import os

dir1 = "new_h_reactivity/"
dir2 = "T2_reactivities/"
dir_w = "corr"
ignore1 = "Coverage"
ignore2 = "nan"
COVERAGE = 1971
PLT_TITLE = "Heatshock vs No Heatshock"

#get coverage value
def get_cov(file_name):
    lc = file_name.readline()
    lc = lc.strip('\n')
    lin = lc.split(' ')
    num = float(lin[-1])
    return num

#calculate correlation between 2 reativity value
def get_corr2(ref, test):
    a_ref, a_test = [], []
    for l1, l2, in zip (ref, test):
        l1 = ref.readline()
        l2 = test.readline()
        if (ignore1 in l1) or (ignore2 in l1) or (l1 == ""):
            continue
        elif (ignore1 not in l2) and (ignore2 not in l2) and (l2 != ""):
            a_ref.append(float(l1))
            a_test.append(float(l2))
        else:
            continue
    # if list end up being less than 2
    if (len(a_ref) <= 1) or (len(a_test) <= 1):
        return "NULL"
    else:
        corr2 = stats.pearsonr(a_ref, a_test)
        return corr2  
      

tot_ave_cov = []
tot_corr = []
for file in os.listdir(dir1):
    if file not in os.listdir(dir2):
	    continue
    f1 = dir1 + file
    f2 = dir2 + file

    h3 = open(f1, 'r')
    c1 = get_cov(h3)

    h4 = open(f2, 'r')
    c2 = get_cov(h4)

    corr = get_corr2(h3, h4)

    if corr != "NULL":
        tot_corr.append(corr)
        tot_ave_cov.append((c1 + c2) / 2)

    h3.close()
    h4.close()

num_corr = []

for ele in tot_corr:
    ele = str(ele)
    ele = ele.split(',')
    ele = str(ele[0])
    ele = ele.split('=')
    pval = float(ele[-1])
    num_corr.append(pval)

print(num_corr)

plt.scatter(tot_ave_cov, num_corr, c = 'black', s = 1)
plt.title(PLT_TITLE)

plt.ylabel("Correlation (R-value) between samples")
plt.xlabel("Avg coverage between samples")
plt.xscale('log')
plt.ylim([-0.2, 1])
plt.axvline(x = COVERAGE, color = 'r', linestyle = 'dashed')
plt.show()