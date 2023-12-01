##program output average mutation rate of each kind of nitro-base for all introns
##input a coverage file and a corresponding deduplicated view file contains\
##intron sequences and their mutation reads
PICK = "chr"
DISCARD = "Num"
#make dictionary of whole coverage file
def mk_dcov(covf):                
    dcov = {}
    line_c = covf.readline()
    while DISCARD not in line_c: 
        lin = line_c.strip('\n')
        lin = lin.split('\t')
        cov = int(lin[-1])
        if cov >= 1971:
            dcov[lin[0]] = cov
        line_c = covf.readline()
    return dcov

#make mutation percent of each kind of base for each intron
def calc_mut(seq, mut, read):       
    ct_a, ct_t, ct_c, ct_g, perc_a, perc_t, perc_c, perc_g = 0,0,0,0,0,0,0,0
    for (i, j, k) in zip(seq, mut, read):
        mpercent = int(j) / int(k) * 100
        if i == "A":
            ct_a += 1
            perc_a += mpercent
        elif i == "T":
            ct_t += 1
            perc_t += mpercent
        elif i == "C":
            ct_c += 1
            perc_c += mpercent
        elif i == "G":
            ct_g += 1
            perc_g += mpercent
    ave_a = perc_a / ct_a
    ave_t = perc_t / ct_t
    ave_c = perc_c / ct_c
    ave_g = perc_g / ct_g
    return ave_a, ave_t, ave_c, ave_g

#main            
covf_name = input("input coverage file name:")
covf = open(covf_name, "r")
viewf_name = input('input view file name:')
viewf = open(viewf_name, "r")

tot_a, tot_t, tot_c, tot_g, index = 0,0,0,0,0
dict_cov = mk_dcov(covf)
print(dict_cov)
line_f = viewf.readline()
while line_f:
    if PICK in line_f:
        key = line_f.strip('\n')
        line_f = viewf.readline()
        seq = line_f.strip('\n')
        line_f = viewf.readline()
        l3 = line_f.strip('\n')
        mut = l3.split(",")
        line_f = viewf.readline()
        l4 = line_f.strip('\n')
        read = l4.split(",")
    else:
        key, seq = "none", "none"  
        mut, read = [0], [0]
    line_f = viewf.readline()
    if key in dict_cov:
        index += 1
        ave_a, ave_t, ave_c, ave_g = calc_mut(seq, mut, read)
        tot_a += ave_a
        tot_t += ave_t
        tot_c += ave_c
        tot_g += ave_g
    else:
        pass
A = tot_a / index
T = tot_t / index
C = tot_c / index
G = tot_g / index

all = A + T + C + G
A_over_all = A / all * 100
T_over_all = T / all * 100
C_over_all = C / all * 100
G_over_all = G / all * 100
print("**STATISTICS of ", viewf_name, ":\n\n")
print ("mutation A: ", A, "\nmutation T: ", T,\
     "\nmutation C: ", C, "\nmutation G: ", G)
print ("one base over all mutation in percent:", "\nA over all: ", A_over_all,\
    "\nT over all: ", T_over_all, "\nC over all: ", C_over_all,\
    "\nG over all: ", G_over_all)

covf.close()
viewf.close()

## I_coverage.txt
## I_dedup_view.txt
#. T_coverage.txt
#  T_dedup_view.txt



