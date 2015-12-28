/*
  falab - free algorithm lab 
  Copyright (C) 2012 luolongzhi (Chengdu, China)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.


  filename: fa_getopt.c 
  version : v1.0.0
  time    : 2012/07/08 18:42 
  author  : luolongzhi ( falab2012@gmail.com luolongzhi@gmail.com )

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __GNUC__ 
#include <getopt.h>
#else
#include "getopt.h"
#endif

#include "fa_parseopt.h"
#include "fa_fir.h"
#include "fa_fft.h"
#include "fa_mdct.h"


/*global option vaule*/
char  opt_inputfile[256]  = "1m.wav";
/*char  opt_inputfile[256]  = "xs-mono.wav";//"1m.wav";*/
char  opt_outputfile[256] = "1m-out.wav";
int   opt_framelen  = 512;
int   opt_fftwintype    = BLACKMAN; //KAISER; //SINE; //BLACKMAN; //HAMMING;
int   opt_mdctwintype   = MDCT_SINE; //MDCT_KBD;

enum{
    OPT_FFTWINTYPE = 300,
    OPT_MDCTWINTYPE,
};


const char *usage =
"\n\n"
"Usage: fapsychomodel <-i> <inputfile> <-o> <outputfile> [options] \n"
"\n\n"
"See also:\n"
"    --help               for short help on ...\n"
"    --long-help          for a description of all options for ...\n"
"    --license            for the license terms for falab.\n\n";

const char *default_set =
"\n\n"
"No argument input, run by default settings\n"
"    --framesize  [1024]\n"
"\n\n";

const char *short_help =
"\n\n"
"Usage: fapsychomodel <-i> <inputfile> <-o> <outputfile> [options] ...\n"
"Options:\n"
"    -i <inputfile>       Set input filename\n"
"    -o <outputfile>      Set output filename\n"
"    -l <len>             Set frame length\n"
"    --help               Show this abbreviated help.\n"
"    --long-help          Show complete help.\n"
"    --license            for the license terms for falab.\n"
"\n\n";

const char *long_help =
"\n\n"
"Usage: fapsychomodel <-i> <inputfile> <-o> <outputfile> [options] ...\n"
"Options:\n"
"    -i <inputfile>       Set input filename\n"
"    -o <outputfile>      Set output filename\n"
"    -l                   Set frame length\n"
"    --help               Show this abbreviated help.\n"
"    --long-help          Show complete help.\n"
"    --license            for the license terms for falab.\n"
"    --input <inputfile>  Set input filename\n"
"    --output <inputfile> Set input filename\n"
"    --framelen <len>     Set frame length to process\n"
"    --winlen <len>       Set window length to process\n"
"    --fftwintype <type>  Set fft trans window type to process\n"
"    --mdctwintype <type> Set mdct trans window type to process\n"
"\n\n";

const char *license =
"\n\n"
"**************************************  WARN  *******************************************\n"
"*    Please note that the use of this software may require the payment of patent        *\n"
"*    royalties. You need to consider this issue before you start building derivative    *\n"
"*    works. We are not warranting or indemnifying you in any way for patent royalities! *\n"
"*                                                                                       *\n" 
"*                YOU ARE SOLELY RESPONSIBLE FOR YOUR OWN ACTIONS!                       *\n"
"*****************************************************************************************\n"
"\n"
"\n"
"falab - free algorithm lab \n"
"Copyright (C) 2012 luolongzhi (Chengdu, China)\n"
"\n"
"This program is free software: you can redistribute it and/or modify\n"
"it under the terms of the GNU General Public License as published by\n"
"the Free Software Foundation, either version 3 of the License, or\n"
"(at your option) any later version.\n"
"\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
"\n"
"You should have received a copy of the GNU General Public License\n"
"along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
"\n"
"\n"
"falab src code is based on the signal processing theroy, optimize theroy, ISO ref, etc.\n"
"The purpose of falab is building a free algorithm lab to help people to learn\n"
"and study algorithm, exchanging experience.    ---luolongzhi 2012.07.08"
"\n";

static void fa_printopt()
{
    FA_PRINT("NOTE: configuration is below\n");
    FA_PRINT("NOTE: inputfile = %s\n", opt_inputfile);
    FA_PRINT("NOTE: outputfile= %s\n", opt_outputfile);
    FA_PRINT("NOTE: framelen  = %d\n", opt_framelen);
    FA_PRINT("NOTE: wintype   = %d\n", opt_fftwintype);
    FA_PRINT("      (0:hamming; 1:blackman; 2:kaiser)\n");
}

/**
 * @brief: check the input value valid, should check the valid scope
 *
 * @return: 0 if success, -1 if error
 */
static int fa_checkopt(int argc)
{
/*
    if(argc < 5) {
        FA_PRINT_ERR("FAIL: input and output file should input\n");
        return -1;
    }
*/
    if(strlen(opt_inputfile) == 0 || strlen(opt_outputfile) == 0) {
        FA_PRINT_ERR("FAIL: input and output file should input\n");
        return -1;

    }

    if(opt_framelen > 8192) {
        FA_PRINT_ERR("FAIL: the frame length is too large, should <= 8192\n");
        return -1;
    }

    if(opt_fftwintype < HAMMING || opt_fftwintype > KAISER) {
        FA_PRINT_ERR("FAIL: fft window type wrong, only 0,1,2,3 active\n");
        return -1;
    }

    if(opt_mdctwintype < MDCT_SINE || opt_mdctwintype > MDCT_KBD) {
        FA_PRINT_ERR("FAIL: mdct window type wrong, only 0,1 active\n");
        return -1;
    }

    FA_PRINT("SUCC: check option ok\n");
    return 0;
}


/**
 * @brief: parse the command line
 *         this is the simple template which will be used by falab projects
 *
 * @param:argc
 * @param:argv[]
 *
 * @return: 0 if success, -1 if error(input value maybe not right)
 */
int fa_parseopt(int argc, char *argv[])
{
    int ret;
    const char *die_msg = NULL;

    while (1) {
        static char * const     short_options = "hHLi:o:l:t:";  
        static struct option    long_options[] = 
                                {
                                    { "help"       , 0, 0, 'h'}, 
                                    { "long-help"  , 0, 0, 'H'},
                                    { "license"    , 0, 0, 'L'},
                                    { "input"      , 1, 0, 'i'},                 
                                    { "output"     , 1, 0, 'o'},                 
                                    { "framelen"   , 1, 0, 'l'},        
                                    { "fftwintype" , 1, 0, OPT_FFTWINTYPE},        
                                    { "mdctwintype" , 1, 0, OPT_MDCTWINTYPE},        
                                    {0             , 0, 0,  0},
                                };
        int c = -1;
        int option_index = 0;

        c = getopt_long(argc, argv, 
                        short_options, long_options, &option_index);

        if (c == -1) {
            break;
        }

        if (!c) {
            die_msg = usage;
            break;
        }

        switch (c) {
            case 'h': {
                          die_msg = short_help;
                          break;
                      }

            case 'H': {
                          die_msg = long_help;
                          break;
                      }
                      
            case 'L': {
                          die_msg = license;
                          break;
                      }

            case 'i': {
                          if (sscanf(optarg, "%s", opt_inputfile) > 0) {
                              FA_PRINT("SUCC: inputfile is %s\n", opt_inputfile);
                          }else {
                              FA_PRINT_ERR("FAIL: no inputfile\n");
                          }
                          break;
                      }

            case 'o': {
                          if (sscanf(optarg, "%s", opt_outputfile) > 0) {
                              FA_PRINT("SUCC: outputfile is %s\n", opt_outputfile);
                          }else {
                              FA_PRINT_ERR("FAIL: no outputfile\n");
                          }
                          break;
                      }

            case 'l': {
                          unsigned int i;
                          if (sscanf(optarg, "%u", &i) > 0) {
                              opt_framelen = i;
                              FA_PRINT("SUCC: set frame length = %u\n", opt_framelen);
                          }
                          break;
                      }

            case OPT_FFTWINTYPE: {
                          unsigned int i;
                          if (sscanf(optarg, "%u", &i) > 0) {
                              opt_fftwintype = i;
                              FA_PRINT("SUCC: set fft win type = %u\n", opt_fftwintype);
                          }
                          break;
                      }

            case OPT_MDCTWINTYPE: {
                          unsigned int i;
                          if (sscanf(optarg, "%u", &i) > 0) {
                              opt_mdctwintype = i;
                              FA_PRINT("SUCC: set mdct win type = %u\n", opt_mdctwintype);
                          }
                          break;
                      }

            case '?':
            default:
                      die_msg = usage;
                      break;
        }
    }

    if(die_msg) {
        FA_PRINT("%s\n", die_msg);
        goto fail;
    }

    /*check the input validity*/
    ret = fa_checkopt(argc);
    if(ret) {
        die_msg = usage;
        FA_PRINT("%s\n", die_msg);
        goto fail;
    }

    /*print the settings*/
    fa_printopt();

    return 0;
fail:
    return -1;
}