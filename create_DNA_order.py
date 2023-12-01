#! env python3

import argparse

parser = argparse.ArgumentParser(
                    prog = 'create_DNA_order.py',
                    description = 'create Twist DNA order for RYOP cloud labs, 2022-');

parser.add_argument('filename',help='Name of .tsv file with name and sequence')
parser.add_argument('--barcode_length','-b',default=8,type=int,help='length of stretch before 3'' 20-nt TAIL2 sequence that is guaranteed to be unique')
parser.add_argument('--forward_primer_sequence',default='',type=str,help='forward primer sequence to check for in library')
parser.add_argument('--reverse_primer_sequence',default='',type=str,help='forward primer sequence to check for in library')
parser.add_argument('--slice_5prime',default=0,type=int,help='Number of nts to remove from 5'' to prepare DNA order')


args = parser.parse_args()
print( args.filename )
barcode_length = args.barcode_length;

max_seqs = 0 # just run once.

# which column has sequence?
lines = open( args.filename ).readlines()
line1 = lines[0]
#seq_idx = line1.split().index('sequence')
seq_idx = -1

id_idx = line1.split('\t').index('id')

def reverse_complement( seq ):

    rc = {'A':'T','T':'A','C':'G','G':'C'}
    seq_rc = ''
    for i in range(len(seq)):
        seq_rc += rc[ seq[-i-1] ]
    return seq_rc

outfile = args.filename.replace(' ','_') + '.DNA_ORDER.txt'
fid = open( outfile, 'w' )

outfile_twist = args.filename.replace(' ','_') + '.TWIST.csv'
fid_twist = open( outfile_twist, 'w' )
fid_twist.write('name,sequence\n')

outfile_twist2 = args.filename.replace(' ','_') + '.TWIST.txt'
fid_twist2 = open( outfile_twist2, 'w' )

seq_len1 = 0
forward_primer_sequence = args.forward_primer_sequence
reverse_primer_sequence = args.reverse_primer_sequence
reverse_primer_len = len(reverse_primer_sequence)
barcode_list = []
num_seqs = len( lines ) - 1
count = 0

if max_seqs == 0:
    max_seqs = num_seqs
    print( 'Will look for following number of sequences: ',max_seqs )

while count < max_seqs:
    for line in lines[1:]:
        rna_sequence = line.split('\t')[seq_idx].replace('\n','').replace(' ','')
        dna_sequence = rna_sequence.replace('U','T')[6:]

        # check if forward primer sequence is fixed
        # if len( forward_primer_sequence ) == 0: forward_primer_sequence = rna_sequence[:26].replace('U','T')
        # assert( rna_sequence[:len(forward_primer_sequence)].replace('U','T') == forward_primer_sequence )

        # # check if reverse primer sequence is fixed
        # if len( reverse_primer_sequence ) == 0: reverse_primer_sequence = reverse_complement( rna_sequence[-20:].replace('U','T') )
        # assert( reverse_complement( rna_sequence[-1*reverse_primer_len:].replace('U','T') ) == reverse_primer_sequence )

        # process DNA sequence
        rna_seq_len = len(rna_sequence)
        dna_sequence = dna_sequence[args.slice_5prime:]

        # check if sequence length is same across library
        seq_len = len(dna_sequence)
        if seq_len1 == 0: seq_len1 = seq_len
        assert(seq_len == seq_len1 )

        # barcode = rna_sequence[-reverse_primer_len-barcode_length:-reverse_primer_len]
        # if count < num_seqs:
        #     assert( barcode_list.count( barcode ) == 0)
        #     barcode_list.append( barcode )

        fid.write( dna_sequence+'\n' )
        id = line.split('\t')[id_idx]
        if count < num_seqs:
            fid_twist.write( '%s,%s\n' % (id,dna_sequence) )
            fid_twist2.write( '%s\n' % (dna_sequence) )
        count = count+1
        if count % 10000 == 0: print('Finished sequence',count)
        if count == max_seqs: break

fid.close()
fid_twist.close()
fid_twist2.close()

print ()
print( 'RNA Sequence length: %d' % rna_seq_len )
print( 'DNA Sequence length: %d' % seq_len )
print( 'Number of sequences in files: %d'% num_seqs )
print( 'Number of sequences outputted to library: %d' % max_seqs )
print( 'Forward primer sequence: %s' % forward_primer_sequence )
print( 'Reverse primer sequence: %s' % reverse_primer_sequence )
print()
print( 'Output CustomArray DNA order to file: %s' % outfile )
print( 'Output Twist DNA order (CSV) to file: %s' % outfile_twist )
print( 'Output Twist DNA order (just sequences) to file: %s' % outfile_twist2 )


