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
  time    : 2012/07/08 00:42 
  author  : luolongzhi ( falab2012@gmail.com luolongzhi@gmail.com )

  comment : this file is the simple template which will be used in falab,
            it will be changed according to the project.

*/

#include <stdio.h>
#include <stdlib.h>

#ifdef __GNUC__ 
#include <getopt.h>
#else
#include "getopt.h"
#endif

#include "fa_parseopt.h"

enum {
    SWITCH1_FLAG = 100,
    SWITCH2_FLAG,
};

/*global option vaule*/
int opt_verbose     = 0;
int opt_fast        = 0;
int opt_bitrate     = 128;
int opt_samplerate  = 44100;
int opt_switch1     = 1;
int opt_switch2     = 73;


const char *usage =
"\n\n"
"Usage: testprint [options] \n"
"\n\n"
"See also:\n"
"    --help               for short help on ...\n"
"    --long-help          for a description of all options for ...\n"
"    --license            for the license terms for falab.\n\n";

const char *default_set =
"\n\n"
"No argument input, run by default settings\n"
"    --verbose     [off]\n"
"    --fast        [off]\n"
"    --bitrate     [128kbps]\n"
"    --samplerate  [44.1kHz]\n"
"    --switch1     [on]\n"
"    --switch2     [73]\n"
"\n\n";

const char *short_help =
"\n\n"
"Usage: testprint [options] ...\n"
"Options:\n"
"    -v                   Set to verbose mode, show the detail message\n"
"    -f                   Set to fast mode\n"
"    -b <bitrate>         Set average bitrate to x kbps.\n"
"    -R <samplerate>      Set samplerate.\n"
"    --help               Show this abbreviated help.\n"
"    --long-help          Show complete help.\n"
"    --license            for the license terms for falab.\n"
"    --switch1            Set switch1 enable\n"
"    --switch2 <value>    Set switch2 value, need argument\n"
"\n\n";

const char *long_help =
"\n\n"
"Usage: testprint [options] ...\n"
"Options:\n"
"    -v                   Set to verbose mode, show the detail message\n"
"    -f                   Set to fast mode\n"
"    -b <bitrate>         Set average bitrate to x kbps.\n"
"                         (test set one value, take bitrate as an example)\n"
"    -R <samplerate>      Set samplerate.\n"
"    --help               Show this abbreviated help.\n"
"    --long-help          Show complete help.\n"
"    --long-help          Show complete help.\n"
"    --switch1            Set switch1 enable\n"
"                         (test switch enable, and short argument can not enable it)\n"
"    --switch2 <value>    Set switch2 value, need argument\n"
"                         (test switch set, and short argument can not enable it)\n"
"\n\n"
"Note:\n"
"  This source file is the template of the falab project argument\n"
"  line, all of the source will adjust according to this template\n"
"\n"
"\n";

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
    FA_PRINT("NOTE: verbose   : %u\n", opt_verbose);
    FA_PRINT("NOTE: fast      : %u\n", opt_fast);
    FA_PRINT("NOTE: bitrate   : %u\n", opt_bitrate);
    FA_PRINT("NOTE: samplerate: %u\n", opt_samplerate);
    FA_PRINT("NOTE: switch1   : %u\n", opt_switch1);
    FA_PRINT("NOTE: switch2   : %u\n", opt_switch2);
}

/**
 * @brief: check the input value valid, should check the valid scope
 *
 * @return: 0 if success, -1 if error
 */
static int fa_checkopt(int argc)
{
    if(argc < 2) {
        FA_PRINT("%s\n", default_set);
        return 0;
    }

    /*this is just example*/
    if(opt_samplerate > 48000) {
        FA_PRINT_ERR("FAIL: the samplerate is not right\n");
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
        static char * const     short_options = "hHLvfb:R:";  
        static struct option    long_options[] = 
                                {
                                    { "help"       , 0, 0, 'h'}, 
                                    { "long-help"  , 0, 0, 'H'},
                                    { "license"    , 0, 0, 'L'},
                                    { "verbose"    , 0, 0, 'v'},  
                                    { "fast"       , 0, 0, 'f'},  
                                    { "bitrate"    , 1, 0, 'b'},                // need 1 argument 
                                    { "samplerate" , 1, 0, 'R'},                // need 1 argument 
                                    { "switch1"    , 0, 0, SWITCH1_FLAG},       // --switch1 will return SWIATCH1_FLAG 
                                    { "switch2"    , 1, 0, SWITCH2_FLAG},       // --switch2 will return SWIATCH2_FLAG 
                                    {0             , 0, 0, 0},
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

            case 'v': {
                          opt_verbose = 1;
                          FA_PRINT("SUCC: verbose mode active\n");
                          break;
                      }

            case 'f': {
                          opt_fast = 1;
                          FA_PRINT("SUCC: fast mode active\n");
                          break;
                      }

            case 'b': {
                          unsigned int i;
                          if (sscanf(optarg, "%u", &i) > 0) {
                              opt_bitrate = 1000 * i;
                              FA_PRINT("SUCC: set bitrate=%u\n", opt_bitrate);
                          }else {
                              opt_bitrate = 0;
                              FA_PRINT("WARN: bitrate not set\n");
                          }
                          break;
                      }

            case 'R': {
                          unsigned int i;
                          if (sscanf(optarg, "%u", &i) > 0) {
                              opt_samplerate = i;
                              FA_PRINT("SUCC: set samplerate=%u\n", opt_samplerate);
                          }else {
                              opt_samplerate = 0;
                              FA_PRINT("WARN: samplerate not set\n");
                          }
                          break;
                      }

            case SWITCH1_FLAG:{
                                  opt_switch1 = 1;
                                  FA_PRINT("SUCC: switch1 set, default = 1 \n");
                                  break;
                              }

            case SWITCH2_FLAG:{
                                  unsigned int i;
                                  if (sscanf(optarg, "%d", &i) > 0) {
                                      opt_switch2 = i;
                                      FA_PRINT("SUCC: set switch2=%d\n", opt_switch2);
                                  }else {
                                      opt_switch2 = 0;
                                      FA_PRINT("WARN: switch2 not set\n");
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
        goto fail;
    }

    /*print the settings*/
    fa_printopt();

    return 0;
fail:
    return -1;
}
