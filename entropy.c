#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double calculate_entropy(unsigned int *dist, unsigned int num_chars);

int main(int argc,char* argv[]) {

        char *input_file;
        if (argc != 2) {
                puts("Invalid command line arguments");
                return -1;
        }
        else {
                input_file = argv[1];
        }

        unsigned int character_dist[256]={};
        
        FILE *input_fp = fopen(input_file, "r");
        if (NULL == input_fp) {
                puts("Unable to open filename");
                return -1;
        }

        char c;
        unsigned int total_num_characters = 0;
        while(EOF != (c=getc(input_fp))) {
                 int i = c;
                character_dist[i]++;
                total_num_characters++;
        }
        
        double entropy = calculate_entropy(character_dist, total_num_characters);
        printf("The entropy of the given text file is: %.4f\n", entropy);
}


double calculate_entropy(unsigned int *dist, unsigned int num_chars) {

        double ent = 0.0;

        int i;
        //C doesn't have a function to choose base of log
        //Just use property log base b of x = log(x)/log(b)

        double constant_factor = 1.0/log10(2);
        for(int i = 0; i < 255; i++) {
                double px = dist[i]/(double)num_chars;
                if(px == 0.0) {
                        continue;
                }
                ent+= (px*(log10(px)*constant_factor));
        }
        return fabs(ent);

}
