/*
 * the hipoclock is an open source project for Enterprise central
 * tasks scheduling for the Unix/Linux platform
 * Copyright (C) yyyy  Oren Oichman
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Gnomovision version 1, Copyright (C) Oren Oichman
 * Gnomovision comes with ABSOLUTELY NO WARRANTY; for details
 * type `canoectl -h'.  This is free software, and you are welcome
 * to redistribute it under certain conditions; type `canoectl -h' 
 * for details.
 */

#include "hipoclockd.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"

#if !defined(HIPO_BASEETC) 
#define HIPO_BASEETC "/usr/local/etc"
#endif

#define HIPOSRV_CONF HIPO_BASEETC"/hipoclock/hipoclockd.conf"

#if !defined(HIPO_EXEC)
#define HIPO_EXEC "/usr/local/libexec"
#endif

#if !defined(HIPO_VAR)
#define HIPO_VAR "/usr/local/var"
#endif

#define HIPOSRV_SQLITE_FILE HIPO_VAR"/lib/hipod/hipoclockd.sl3"


void Help(int rcode) {

	printf("Usage:  hipoclockd\n");
        printf("\t\t -v - Be Verbose when running the Daemon\n");
        printf("\t\t -h - Display this manu\n");
        printf("\t\t -i - the Bind IP address (default : ALL) \n");
        printf("\t\t -p - Bind to the fallowing tcp port (default : 9797) \n");
        printf("\t\t -u - Bind to the fallowing udp port  (default : 9799) \n");
        printf("\t\t -t - test the configuration file \n");
        printf("\t\t -s - use sqlite database file (Default %s) \n",HIPOSRV_SQLITE_FILE);
        printf("\t\t -d - the ODBC DSN to use for database connection (force odbc database usage) \n");
        printf("\t\t -c - set an alternative configuration file (Default: hipoclockd.conf ) \n");
        printf("\n");

	exit(rcode);
}


int main(int argc,char *argv[]) {

	int args_i=0;
	int tcp_port=9797,udp_port=9799;
	char *dsnName=NULL, *bindAddress = NULL;
	FILE *ifile = NULL;
	char *confName=NULL,*sqliteName=NULL;

	arg_options arg_opt = { 0 , 0 ,0 ,0 ,0 };

	while ((args_i = getopt (argc, argv, "vhi:p:u:t:s:d:c:")) != -1)
		switch(args_i) {
			case 'v':
				arg_opt.ver_opt=1;
			break;

			case 'h':
				Help(0);
			break;

			case 'i':
				bindAddress = optarg;
				arg_opt.newip_opt=1;
			break;

			case 'p':
				tcp_port= atoi(optarg);
			break;

			case 'u':
				udp_port = atoi(optarg);
			break;

			case 't':
				arg_opt.testfile_opt=1;
			break;

			case 's':
				sqliteName = optarg;
			break;
			case 'd':
				dsnName = optarg;
			break;

			case 'c':
				 if (ifile = fopen(optarg,"rt")){
                                        printf("the file %s is o.k.\n",optarg);
                                        arg_opt.file_opt = 1;
                                }
                                else {
                                        fprintf(stderr,"the file \"%s\" can not be opened\n",optarg);
                                        exit(1);
                                }

			break;
	
			case '?':	

				if ( (optopt == 'i') || (optopt == 'd') || (optopt == 'c') ) {
                           		fprintf (stderr," " "Option -%c requires an argument.\n", optopt);
                        	}
                        
				else if (isprint (optopt)) {
                                	fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                        	}
                        
				else {
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
					exit(EXIT_FAILURE);
				}

			break;

			default:
				Help(1);
			break;
		
		}

	// checking for multiple database selection
	
	if ( (sqliteName != NULL) && (dsnName != NULL ) ) {
		fprintf(stderr,"Error 111 - only one Database type should be specified\n");
		Help(2);
	}

	// checking Verbose mode
	if ( arg_opt.ver_opt == 1 )
		printf("starting the Daemon in Verbose mode\n");
	
	// checking for different configuration file
	//
	if ( arg_opt.file_opt == 0 ) {

		confName = HIPOSRV_CONF;
		if ( arg_opt.ver_opt == 1 )
			printf("openning the file %s for reading\n", confName);

                if (ifile = fopen(confName,"rt")) {
			arg_opt.file_opt = 1;
                }

		else {
			fprintf(stderr,"the file \"%s\" Can not be opened\n",confName);
			exit(1);
		}
	}
		
	//hipo_check_args(&argc,&argv);

	return 0;
}
