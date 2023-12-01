%%%%%%%%%%
%% Read in data
filedir = './';
[m,c,rc,tags] = read_ubr_output( filedir,[],1 );
[ids,titles,authors,headers,sequences] = get_sequence_info( 'pseudoknot50_puzzle_11318423.tsv.RNA_sequences.fa' );
[ structures, structure_map ] = read_structure_csv_file( 'ryop50_NUPACK.csv', sequences );
BLANK_OUT5 = 26; % forward primer
BLANK_OUT3 = 20; % reverse primer
shape_nomod_idx = { [1,3],[2,4] };
[r,r_err,f,f_err,coverage,signal_to_noise] = get_reactivity(m,c,shape_nomod_idx,BLANK_OUT5,BLANK_OUT3);
for i = 1:length(shape_nomod_idx); conditions{i} = tags{ shape_nomod_idx{i}(1)}; end
COVERAGE_CUTOFF = 10000; % stringent cutoff.
good_idx = find( sum(coverage,2) > COVERAGE_CUTOFF );
[r_norm, r_norm_err] = normalize_reactivity(r,r_err,good_idx,BLANK_OUT5, BLANK_OUT3, conditions );
%[r_norm_by_nt, r_norm_by_nt_err] = normalize_reactivity_by_nt_type(r,r_err,sequences,good_idx,BLANK_OUT5, BLANK_OUT3, conditions );
%% Make plot of signal-to-noise vs. data
plot(coverage(:,end),signal_to_noise(:,end),'.')
xlabel('Coverage in SHAPE,Mg2+')
ylabel('Signal/noise SHAPE, Mg2+');
%% Histogram of signal to noise
set(figure(2),'color','white')
for i = 1:size(r,3)
   subplot(size(r,3),1,i);
   s2n = signal_to_noise(:,i); s2n( find(isnan(s2n)) ) = 0.0;
   histogram( s2n )
   xlabel( 'Signal/noise' );
   title( {filedir,tags{shape_nomod_idx{i}(1)},['Mean signal/noise = ',num2str(mean(s2n))]},'interp','none');
   fprintf( 'Mean signal-to-noise (%s) %f\n',tags{shape_nomod_idx{i}(end)},mean(s2n) );
end
%%
COVERAGE_CUTOFF = 10000;
%COVERAGE_CUTOFF = 20000;
%COVERAGE_CUTOFF = 100000; % stringent cutoff.
good_idx = find( sum(coverage,2) > COVERAGE_CUTOFF );
%make_library_heat_map( r_norm(:,:,1), good_idx, structure_map, headers, BLANK_OUT5, BLANK_OUT3);
make_library_heat_map( r_norm, good_idx, structure_map, headers, BLANK_OUT5, BLANK_OUT3,conditions);
%% Take a close look at one of the constructs with high apparent signal to noise, but negative features
figure(3);clf;
set(gcf,'color','white')
idx = 2112; % IceBolt
%idx = 2655; %Anamfija Orchid Updated
%idx = 2027; %glutamine riboswitch
for i = 1:size(r,3)
   subplot(size(r,3),1,i);
   plot( squeeze(f(idx,:,shape_nomod_idx{i})),'LineWidth',2 )
   h = legend( tags(shape_nomod_idx{i}));
   set(h,'interp','none')
end
h=title(headers(idx));
set(h,'interpreter','none')
%% Make some heatmaps
set(figure(4),'color','white')
Nconditions = size(f,3);
for i = 1:Nconditions
   subplot(1,Nconditions,i)
   %imagesc(m(:,:,i),[0 1000]);
   imagesc(f(:,:,i),[0 0.1])
   colormap(1-gray(100));
   title(tags{i},'interpreter','none')
   ylim([0 500]); % zoom in on first 500
end

%% Score folding algorithms!
%mfe_structures_csv_file = 'ProcessedRYOP90.csv';
%mfe_structures_csv_file = 'PK90+HFold.csv';
%mfe_structures_csv_file = 'PK90_HFoldByHand.csv';
mfe_structures_csv_file = 'PK50-7Apr23-EDITED.csv';
[x,mfe_tags, mfe_structures,mfe_structure_map] = read_mfe_structures_csv_file( mfe_structures_csv_file );

%% Get correlation coefficient table.
COVERAGE_CUTOFF = 10000;
good_idx = find( sum(coverage,2) > COVERAGE_CUTOFF );
for i = [2 1]
   fprintf('\nCorrelation coefficients over %d sequences with total counts > %d, %s\n',length(good_idx),COVERAGE_CUTOFF,tags{shape_nomod_idx{i}(1)});
   [all_corr_coef, pkg_sort_idx] = get_corr_coeff( r(:,:,i), mfe_structure_map, good_idx, mfe_tags, BLANK_OUT3, BLANK_OUT5);
end

%% Look through each of the conditions - mutational profiles (mean over designs)
run_mut_type_analysis( m,c,rc,tags,tags,BLANK_OUT5, BLANK_OUT3)

%% RDAT
filename = 'data_sets/release/CustomArrayPK50_1M7_NovoSeq.rdat';
name = 'OpenKnotPilot_PK50';
COVERAGE_CUTOFF = 10000;
good_idx = find( sum(coverage,2) > COVERAGE_CUTOFF );
comments = {'Output of UBR',...
   'from data: oak/rui/Novogene/PK50_90_march2023',...
   '1M7-based SHAPE mutational profiling',...
   'Library ordered from Twist',...
   };
annotations = {'modifier:1M7','chemical:HEPES:50mM(pH8.0)','chemical:MgCl2:10mM','temperature:24C','processing:RNAFramework-v2.8.2'};
extra_data_annotations = get_extra_data_annotations_for_eterna( ids, titles, authors );
rdat = output_rdat_from_ubr_analysis( filename, name, good_idx, r_norm(:,:,2), r_norm_err, sequences, structures, BLANK_OUT5, BLANK_OUT3, comments, annotations, extra_data_annotations );
show_rdat(filename); % check that we can read back in from disk.

%% Need to run following on Sherlock:
%   sdev -n16 -p biochem -m 32Gb -t 4:00:00
%   ml load matlab
%   matlab
addpath(genpath('/home/groups/rhiju/rhiju/src/OpenKnotScore/matlab'));
addpath(genpath('/home/groups/rhiju/rhiju/src/RiboKit/packages/Biers/Scripts'));
addpath(genpath('/home/groups/rhiju/rhiju/src/RiboKit/packages/RDATKit/MATLAB'));
parpool();
rdat_file = 'data_sets/release/CustomArrayPK50_1M7_NovoSeq.rdat';
r = read_rdat_file( rdat_file );
[r_norm,sequences,BLANK_OUT5,BLANK_OUT3] = get_r_norm_from_rdat( r );
good_idx = [1:length(sequences)];
structures_shapeknots(good_idx) = run_shapeknots( sequences, r_norm, good_idx, BLANK_OUT5, BLANK_OUT3 );
output_structures_csv( 'RHEt1_Novoseq_CustomArrayPK50_1M7_SHAPEknots_structures_march2023.csv','SHAPEknots',structures_shapeknots, sequences )