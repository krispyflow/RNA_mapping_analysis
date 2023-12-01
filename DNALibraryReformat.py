from Bio import SeqIO
import pandas as pd
temp_seqs = list(SeqIO.parse('FINAL/FINAL390_clean.fasta', "fasta"))

new_seqs = []
for i,seq in enumerate(temp_seqs):
    title = seq.name
    name = title.split("__")[0]
    sequence = str(seq.seq)
    id_ = i+10000
    body = ''
    new_seqs.append([id_,name,title,body,sequence])
pd.DataFrame(new_seqs,columns=['id','name','title','body','sequence']).to_csv('FINAL/FINAL390_clean.tsv', sep="\t",index=False)
