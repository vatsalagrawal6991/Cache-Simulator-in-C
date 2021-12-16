import os

#path to the submissions 
spath = '/home/abhishek/COP701-Major/COP701-Major-Evaluation-script/submissions'

#path to the traces
tpath = '/home/abhishek/COP701-Major/COP701-Major-Evaluation-script/tests'

#path to the output directory
opath = '/home/abhishek/COP701-Major/COP701-Major-Evaluation-script/output'

#all submission dirs
dirs = [dir for dir in os.listdir(spath) if os.path.isdir(os.path.join(spath, dir))]

#file to store scores of students
scores = open('scores.csv', 'w')


#trace files
tests = ['test1.trace', 'test2.trace', 'test3.trace', 'test4.trace', 'test5.trace']

#combination of configurations to run on the traces
configs = { '1' : [128, 1024, 256, 'LRU'], '2' : [128, 2048, 32, 'FIFO']}

#correct answers of the test cases
results =  {'test1.trace' : { '1' : ['5', '0', '2', '3', '0', '0', '19205'], '2' : ['5', '0', '2', '3', '0', '0', '2405']}, 'test2.trace' : { '1' : ['10', '0', '9', '1', '0', '0', '6410'], '2' : ['10', '0', '9', '1', '0', '0', '810'] }, 'test3.trace' : { '1' : ['9', '0', '8', '1', '0', '0', '6409'], '2' : ['9', '0', '6', '3', '0', '0', '2409'] }, 'test4.trace' : { '1' : ['0', '5', '0', '0', '2', '3', '19205'], '2' : ['0', '5', '0', '0', '2', '3', '2405'] }, 'test5.trace' :  { '1' : ['0', '10', '0', '0', '9', '1', '6401'], '2' : ['0', '10', '0', '0', '9', '1', '810'] }  }

for dir in dirs :
    id = dir.split('_')[0].lower()
    os.chdir(os.path.join(spath, dir))
    score = 0

    for test in tests :
        for config in configs.keys() :
            os.system('make clean')
            os.system('make sim')
            os.system('make run num_sets={sets} num_blocks={blocks} size_block={size} eviction_policy={policy} trace_file={file} output_file={ofile}'.format(sets=configs[config][0], blocks=configs[config][1], size=configs[config][2], policy=configs[config][3], file=os.path.join(tpath, test), ofile=os.path.join(opath, id+'_'+str(config)+test)))

            result = open(os.path.join(opath, id+'_'+str(config)+test), 'r')
            ans = []
            for line in result.readlines():
                ans.append(line.split(':')[1].strip())
            if len(ans)>0:
                for i in range(7):
                    if ans[i] == results[test][config][i]:
                        score += 1
            result.close()
    scores.write(id+","+str(score)+'\n')
    
scores.close()
