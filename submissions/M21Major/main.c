#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int hextodec(char* a, int s, int b){
    int i =0;
    int val=0;
    for(i=0;i<b;i++){
        val=val+ ((a[s+i])*pow(2,i));
    }
    return val;
}

int main(int argc, char* argv[]) {
    typedef enum policya {
        LRU=1, LFU=2, FIFO=3
    }policyb;
    policyb policy = 3;
    int num_setsa = 128;
    int num_blocksa = 2048;
    int size_blocka = 32;
    char fp1[500]="/home/baadalvm/CLionProjects/major/tests/test1.trace";
    char fp2[500]="/home/baadalvm/CLionProjects/major/output/test1.txt";;
    FILE *inp = fopen(fp1, "r");
    FILE *out = fopen(fp2, "w");
    if (argc==7){
        num_setsa= atoi(argv[1]);
        num_blocksa= atoi(argv[2]);
        size_blocka= atoi(argv[3]);
        policy= atoi(argv[1]);
        inp = fopen(argv[5], "r");
        out = fopen(argv[6], "w");
        if(strcmp(argv[4],"LRU")==0){
            policy=1;
        }
        if(strcmp(argv[4],"LFU")==0){
            policy=2;
        }
        if(strcmp(argv[4],"FIFO")==0){
            policy=3;
        }
    }
	if (size_blocka<4){
	printf("size_block not valid");}
    int total_loads=-1;
    int total_stores=-1;
    int load_hits=-1;
    int load_misses=-1;
    int store_hits=-1;
    int store_misses=-1;
    int total_cycles=-1;
    int bits_sets= log(num_setsa)/log(2);
    //int bits_lines= log(num_blocksa)/log(2);
    int bits_block= log(size_blocka)/log(2);
    int bits_tag=32-bits_block-bits_sets;
    //int temp=size_blocka/4;
    int tag[num_setsa][num_blocksa];
    int pol[num_setsa][num_blocksa];
    char dirty[num_setsa][num_blocksa];
    int state=0;
    int m=0,n=0;
    for(m=0;m<num_setsa;m++){
        for(n=0;n<num_blocksa;n++){
            tag[m][n]=-1;
            pol[m][n]=0;
            dirty[m][n]='0';
        }
    }

    char input[30];
    int nolines=0;
    while(fgets(input, 30, inp)!=NULL){
        nolines++;
    };
    rewind(inp);
    char datam[nolines][30];
    int i=0;
    while(fgets(input, 30, inp)!=NULL){
        int j =0;
        for(j=0;j<30;j++){
            datam[i][j]=input[j];
        }
        i++;
    };
    if(policy ==1 ){
        total_loads=0;
        total_stores=0;
        load_hits=0;
        load_misses=0;
        store_hits=0;
        store_misses=0;
        total_cycles=0;
        for(i=0;i<nolines;i++){
            char op= datam[i][0];
            if(op=='l'){
                total_loads++;
            }
            if(op=='s'){
                total_stores++;
            }
            int k=0;
            char address[32];
            for(k=8;k>0;k--){
                if(datam[i][k+3]=='0'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='1'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='2'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='3'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='4'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='5'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='6'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='7'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='8'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='9'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='A'||datam[i][k+3]=='a'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='B'||datam[i][k+3]=='b'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='C'||datam[i][k+3]=='c'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='D'||datam[i][k+3]=='d'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='E'||datam[i][k+3]=='e'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='F'||datam[i][k+3]=='f'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
            }
            int setno = hextodec(address,bits_block,bits_sets);
            int tagno = hextodec(address,bits_block+bits_sets,bits_tag);
            int flag=0; int flag2=0;
            int lineno;
            int lineno2;
            int least=2147483646;
            for(k=0;k<num_blocksa;k++){
                if (tag[setno][k]==-1 && flag==0){
                    flag=1;
                    lineno=k;
                }
                if (tag[setno][k]==tagno){
                    flag2=1;
                    if (op == 's'){
                        store_hits++;
                        dirty[setno][k]='1';
                        pol[setno][k]++;
                    };
                    if (op == 'l'){
                        load_hits++;
                        pol[setno][k]++;
                    };
                    total_cycles++;
                }
                if(pol[setno][k]<least){
                    least=pol[setno][k];
                    lineno2=k;
                }
            }
            if(flag2==0 && flag==1){
                tag[setno][lineno]=tagno;
                if (op == 's'){
                    store_misses++;
                    total_cycles=total_cycles+1+(100*(size_blocka/4));
                    dirty[setno][lineno]='1';
                    pol[setno][k]++;
                };
                if (op == 'l'){
                    load_misses++;
                    total_cycles=total_cycles+1+(100*(size_blocka/4));
                    pol[setno][k]++;
                };

            }
            if(flag2==0 && flag==0){
                tag[setno][lineno2]=tagno;
                if(dirty[setno][lineno2]=='1'){
                    if (op == 's'){
                        store_misses++;
                        total_cycles=total_cycles+1+(2*100*(size_blocka/4));
                        dirty[setno][lineno2]='1';
                        pol[setno][lineno2]=1;
                    };
                    if (op == 'l'){
                        load_misses++;
                        total_cycles=total_cycles+1+(2*100*(size_blocka/4));
                        dirty[setno][lineno2]='0';
                        pol[setno][lineno2]=1;
                    }
                }
                else{
                    if (op == 's'){
                        store_misses++;
                        total_cycles=total_cycles+1+(100*(size_blocka/4));
                        dirty[setno][lineno2]='1';
                        pol[setno][lineno2]=1;
                    };
                    if (op == 'l'){
                        load_misses++;
                        total_cycles=total_cycles+1+(100*(size_blocka/4));
                        dirty[setno][lineno2]='0';
                        pol[setno][lineno2]=1;
                    }
                }
            }
        }
    }
    if(policy ==2){
        total_loads=0;
        total_stores=0;
        load_hits=0;
        load_misses=0;
        store_hits=0;
        store_misses=0;
        total_cycles=0;
        for(i=0;i<nolines;i++){
            char op= datam[i][0];
            if(op=='l'){
                total_loads++;
            }
            if(op=='s'){
                total_stores++;
            }
            int k=0;
            char address[32];
            for(k=8;k>0;k--){
                if(datam[i][k+3]=='0'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='1'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='2'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='3'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='4'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='5'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='6'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='7'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='8'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='9'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='A'||datam[i][k+3]=='a'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='B'||datam[i][k+3]=='b'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='C'||datam[i][k+3]=='c'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='D'||datam[i][k+3]=='d'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='E'||datam[i][k+3]=='e'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='F'||datam[i][k+3]=='f'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
            }
            int setno = hextodec(address,bits_block,bits_sets);
            int tagno = hextodec(address,bits_block+bits_sets,bits_tag);
            int flag=0; int flag2=0;
            int lineno;
            int lineno2;
            int least=2147483646;
            for(k=0;k<num_blocksa;k++){
                if (tag[setno][k]==-1 && flag==0){
                    flag=1;
                    lineno=k;
                }
                if (tag[setno][k]==tagno){
                    flag2=1;
                    if (op == 's'){
                        store_hits++;
                        dirty[setno][k]='1';
                        pol[setno][k]=state++;
                    };
                    if (op == 'l'){
                        load_hits++;
                        pol[setno][k]=state++;
                    };
                    total_cycles++;
                }
                if(pol[setno][k]<least){
                    least=pol[setno][k];
                    lineno2=k;
                }
            }
            if(flag2==0 && flag==1){
                tag[setno][lineno]=tagno;
                if (op == 's'){
                    store_misses++;
                    total_cycles=total_cycles+1+(100*(size_blocka/4));
                    dirty[setno][lineno]='1';
                    pol[setno][k]=state++;
                };
                if (op == 'l'){
                    load_misses++;
                    total_cycles=total_cycles+1+(100*(size_blocka/4));
                    pol[setno][k]=state++;
                };

            }
            if(flag2==0 && flag==0){
                tag[setno][lineno2]=tagno;
                if(dirty[setno][lineno2]=='1'){
                    if (op == 's'){
                        store_misses++;
                        total_cycles=total_cycles+1+(2*100*(size_blocka/4));
                        dirty[setno][lineno2]='1';
                        pol[setno][lineno2]=state++;
                    };
                    if (op == 'l'){
                        load_misses++;
                        total_cycles=total_cycles+1+(2*100*(size_blocka/4));
                        dirty[setno][lineno2]='0';
                        pol[setno][lineno2]=state++;
                    }
                }
                else{
                    if (op == 's'){
                        store_misses++;
                        total_cycles=total_cycles+1+(100*(size_blocka/4));
                        dirty[setno][lineno2]='1';
                        pol[setno][lineno2]=state++;
                    };
                    if (op == 'l'){
                        load_misses++;
                        total_cycles=total_cycles+1+(100*(size_blocka/4));
                        dirty[setno][lineno2]='0';
                        pol[setno][lineno2]=state++;
                    }
                }
            }
        }
    }
    if(policy ==3 ){
        total_loads=0;
        total_stores=0;
        load_hits=0;
        load_misses=0;
        store_hits=0;
        store_misses=0;
        total_cycles=0;
        for(i=0;i<nolines;i++){
            char op= datam[i][0];
            if(op=='l'){
                total_loads++;
            }
            if(op=='s'){
                total_stores++;
            }
            int k=0;
            char address[32];
            for(k=8;k>0;k--){
                if(datam[i][k+3]=='0'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='1'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='2'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='3'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='4'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='5'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='6'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='7'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=0;
                }
                else if(datam[i][k+3]=='8'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='9'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='A'||datam[i][k+3]=='a'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='B'||datam[i][k+3]=='b'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=0;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='C'||datam[i][k+3]=='c'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='D'||datam[i][k+3]=='d'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=0;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='E'||datam[i][k+3]=='e'){
                    address[((8-k)*4)+0]=0;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
                else if(datam[i][k+3]=='F'||datam[i][k+3]=='f'){
                    address[((8-k)*4)+0]=1;
                    address[((8-k)*4)+1]=1;
                    address[((8-k)*4)+2]=1;
                    address[((8-k)*4)+3]=1;
                }
            }
            int setno = hextodec(address,bits_block,bits_sets);
            int tagno = hextodec(address,bits_block+bits_sets,bits_tag);
            int flag=0; int flag2=0;
            int lineno;
            int lineno2;
            int least=2147483646;
            for(k=0;k<num_blocksa;k++){
                if (tag[setno][k]==-1 && flag==0){
                    flag=1;
                    lineno=k;
                }
                if (tag[setno][k]==tagno){
                    flag2=1;
                    if (op == 's'){
                        store_hits++;
                        dirty[setno][k]='1';

                    };
                    if (op == 'l'){
                        load_hits++;
                    };
                    total_cycles++;
                }
                if(pol[setno][k]<least){
                    least=pol[setno][k];
                    lineno2=k;
                }
            }
            if(flag2==0 && flag==1){
                tag[setno][lineno]=tagno;
                if (op == 's'){
                    store_misses++;
                    total_cycles=total_cycles+1+(100*(size_blocka/4));
                    dirty[setno][lineno]='1';
                    pol[setno][k]=state++;
                };
                if (op == 'l'){
                    load_misses++;
                    total_cycles=total_cycles+1+(100*(size_blocka/4));
                    pol[setno][k]=state++;
                };

            }
            if(flag2==0 && flag==0){
                tag[setno][lineno2]=tagno;
                if(dirty[setno][lineno2]=='1'){
                    if (op == 's'){
                        store_misses++;
                        total_cycles=total_cycles+1+(2*100*(size_blocka/4));
                        dirty[setno][lineno2]='1';
                        pol[setno][lineno2]=state++;
                    };
                    if (op == 'l'){
                        load_misses++;
                        total_cycles=total_cycles+1+(2*100*(size_blocka/4));
                        dirty[setno][lineno2]='0';
                        pol[setno][lineno2]=state++;
                    }
                }
                else{
                    if (op == 's'){
                        store_misses++;
                        total_cycles=total_cycles+1+(100*(size_blocka/4));
                        dirty[setno][lineno2]='1';
                        pol[setno][lineno2]=state++;
                    };
                    if (op == 'l'){
                        load_misses++;
                        total_cycles=total_cycles+1+(100*(size_blocka/4));
                        dirty[setno][lineno2]='0';
                        pol[setno][lineno2]=state++;
                    }
                }
            }
        }
    }
    fprintf(out,"Total loads: %d\n",total_loads);
    fprintf(out,"Total stores: %d\n",total_stores);
    fprintf(out,"Load hits: %d\n",load_hits);
    fprintf(out,"Load misses: %d\n",load_misses);
    fprintf(out,"Store hits: %d\n",store_hits);
    fprintf(out,"Store misses: %d\n",store_misses);
    fprintf(out,"Total cycles: %d\n",total_cycles);
    /*printf("Total loads: %d\n",total_loads);
    printf("Total stores: %d\n",total_stores);
    printf("Load hits: %d\n",load_hits);
    printf("Load misses: %d\n",load_misses);
    printf("Store hits: %d\n",store_hits);
    printf("Store misses: %d\n",store_misses);
    printf("Total cycles: %d\n",total_cycles);*/
    fclose(inp);
    fclose(out);
    return 0;
}
