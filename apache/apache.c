/*-------------------------------------------------------------------------
 *
 * apache.c
 *		command-line interface for the Hadoop ecosystem..
 *
 * Copyright (c) 2025 Surafel Temesgen
 *-------------------------------------------------------------------------
 */
 
#include "getopt_long.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <libintl.h>
#include <errno.h>
#include <stdbool.h>

#ifdef _WIN32
#define popen win32_popen
#define pclose _pclose
#endif


static const char *progname = "apache";

/* Options and defaults */
static bool flink = false; /* are we performing a flink operation? */


static void help(const char *progname);
static char * execute_command(const char *command);
FILE *win32_popen(const char *command, const char *type);
static void execute_and_print(const char *command);
static char *apache_strdup(const char *in);

int
main(int argc, char *argv[])
{

	static struct option long_options[] = {
		{"port", required_argument, NULL, 'P'},
		{"all", no_argument, NULL, 'A'},
		{"hdfs", no_argument, NULL, 'h'},
		{"yarn", no_argument, NULL, 'y'},
		{"hbase", no_argument, NULL, 'b'},
		{"spark", no_argument, NULL, 's'},
		{"kafka", no_argument, NULL, 'k'},
		{"zookeeper", no_argument, NULL, 'z'},
		{"flink", no_argument, NULL, 'f'},
		{"storm", no_argument, NULL, 'S'},
		{"metastore", no_argument, NULL, 'm'},
		{"hue", no_argument, NULL, 'u'},
		{"pig", no_argument, NULL, 'p'},
		{"oozie", no_argument, NULL, 'o'},
		{"presto", no_argument, NULL, 'e'},
		{"tez", no_argument, NULL, 't'},
		{"atlas", no_argument, NULL, 'a'},
		{"ranger", no_argument, NULL, 'r'},
		{NULL, 0, NULL, 0}
	};

	int			optindex;
	int			c;
	const char *port = NULL;

	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0)
          {
                help(progname);
                exit(0);
          }
	/* process command-line options */
	while ((c = getopt_long(argc, argv, "A:a:b:f:h:k:m:o:p:P:r:s:S:t:u:y:z",
							long_options, &optindex)) != -1)
	{

		switch (c)
		{
			case 'A':
				execute_and_print("sudo systemctl status atlas");
				execute_and_print("sudo ranger-admin status");
				execute_and_print("hbase shell -c 'status'");
				execute_and_print("hdfs dfsadmin -report");
				execute_and_print("sudo systemctl status presto");
				execute_and_print("spark-shell --master yarn");
				execute_and_print("storm list");
				execute_and_print("yarn node -list");
				execute_and_print("kafka-run-class.sh kafka.tools.JmxTool "
				"--object-name \"kafka.server:type=KafkaServer,name=BrokerState\" "
				"--attributes Value --one-time true");
				execute_and_print("oozie admin -status");
				execute_and_print("yarn application -list -appTypes TEZ");
				execute_and_print("sudo systemctl status hue");
				execute_and_print("pig -version");
				break;
			case 'a':
				execute_and_print("sudo systemctl status atlas");
				break;
			case 'r':
				execute_and_print("sudo ranger-admin status");
				break;
			case 'b':
				execute_and_print("hbase shell -c 'status'");
				break;
			case 'h':
				execute_and_print("hdfs dfsadmin -report");
				break;
			case 'P':
				port = apache_strdup(optarg);
				break;
			case 'm':
				execute_and_print("beeline -u jdbc:hive2://localhost:9083");
				break;
			case 'e':
				execute_and_print("sudo systemctl status presto");
				break;
			case 'f':
				flink = true;
				break;
			case 's':
				execute_and_print("spark-shell --master yarn");
				break;
			case 'S':
				execute_and_print("storm list");
				break;
			case 'y':
				execute_and_print("yarn node -list");
				break;
			case 'k':
				execute_and_print("kafka-run-class.sh kafka.tools.JmxTool "
                          "--object-name \"kafka.server:type=KafkaServer,name=BrokerState\" "
                          "--attributes Value --one-time true");
				break;
			case 'o':
				execute_and_print("oozie admin -status");
				break;
			case 'p':
				execute_and_print("pig -version");
				break;
			case 't':
				execute_and_print("yarn application -list -appTypes TEZ");
				break;
			case 'u':
				execute_and_print("sudo systemctl status hue");
				break;
			case 'z':
				execute_and_print("echo stat | nc localhost 2181");
				break;
			default:
				/* getopt_long already emitted a complaint */
				fprintf(stderr, "Try %s --help for more information.", progname);
				exit(EXIT_FAILURE);
		}
	}

  	if (flink)
	{
		if (port)
		{
			char command[512];
        		snprintf(command, sizeof(command), "flink list -m localhost:%s", port);
        		execute_and_print(command);
        	}
        else
            printf("Port is not specified correctly. Please specify it using the --port option.\n");
        }

	if (optind < argc)
	{
		fprintf(stderr, "too many command-line arguments (first is %s",
					 argv[optind]);
		exit(EXIT_FAILURE);
	}

}

/*
 * help
 *
 * Prints help page for the program
 *
 * progname: the name of the executed program
 */
static void
help(const char *progname)
{
	printf("%s checks the status of Hadoop ecosystem components.\n\n", progname);
	printf("Usage:\n");
	printf("  %s [OPTION]...\n\n", progname);

	printf("Target options:\n");
	printf("   --all               Check the status of all Hadoop ecosystem components.\n");
	printf("  --hdfs                  Provide a summary of the cluster's HDFS status.\n");
	printf("  --yarn                  List all NodeManagers and their statuses.\n");
	printf("  --hbase                 Show the cluster status of HBase.\n");
	printf("  --spark                 Check whether Spark is running.\n");
	printf("  --kafka                 Retrieve all available metrics for all topics within a Kafka broker.\n");
	printf("  --zookeeper             Check the cluster status of Zookeeper.\n");
	printf("  --flink                 Obtain Flink metrics.\n");
	printf("  --storm                 List running topologies.\n");
	printf("  --metastore             Check Hive Metastore reachability.\n");
	printf("  --hue                   Examine Hue status.\n");
	printf("  --pig                   Check if the Pig Grunt interactive shell is operational.\n");
	printf("  --oozie                 Check Oozie server status.\n");
	printf("  --presto                Check Presto cluster statistics.\n");
	printf("  --tez                   List running Tez applications.\n");
	printf("  --atlas                 Check Atlas status.\n");
	printf("  --ranger                Check Ranger status.\n");
	printf("  -p, --port=PORT                flink service port\n");
}

/*
 * Execute a shell command and capture its output.
 *
 * Returns:
 * - A dynamically allocated string containing the command output on success.
 * - NULL on failure (memory allocation failure or command execution error).
 *
 * The caller is responsible for freeing the returned string.
 */
static char *
execute_command(const char *command)
{
    FILE   *fp;
    char    buffer[1024];
    char   *result = NULL;
    size_t  total_size = 0;
    size_t  bytes_read;

    /* Validate input */
    if (command == NULL)
        return NULL;

    /* Open a process to execute the command */
    fp = popen(command, "r");
    if (fp == NULL)
        return NULL;

    /* Read output in chunks */
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        char *temp = realloc(result, total_size + bytes_read + 1); /* +1 for null terminator */
        if (temp == NULL)
        {
            free(result);
            pclose(fp);
            return NULL;
        }
        result = temp;
        memcpy(result + total_size, buffer, bytes_read);
        total_size += bytes_read;
        result[total_size] = '\0'; /* Null-terminate after each chunk */
    }

    /* Handle read errors */
    if (ferror(fp))
    {
        free(result);
        pclose(fp);
        return NULL;
    }

    /* Close the process */
    pclose(fp);

    return result;
}



#if defined(WIN32) && !defined(__CYGWIN__)
#undef system
#undef popen
FILE *
win32_popen(const char *command, const char *type)
{
        size_t          cmdlen = strlen(command);
        char       *buf;
        int                     save_errno;
        FILE       *res;

        /*
         * Create a malloc'd copy of the command string, enclosed with an extra
         * pair of quotes
         */
        buf = malloc(cmdlen + 2 + 1);
        if (buf == NULL)
        {
                errno = ENOMEM;
                return NULL;
        }
        buf[0] = '"';
        memcpy(&buf[1], command, cmdlen);
        buf[cmdlen + 1] = '"';
        buf[cmdlen + 2] = '\0';

        res = _popen(buf, type);

        save_errno = errno;
        free(buf);
        errno = save_errno;

        return res;
}
#endif

static void
execute_and_print(const char *command)
{
    char *output = execute_command(command);

    if (output != NULL)
    {
        printf("%s\n", output);
        free(output); /* Free the allocated memory */
    }
    else
    {
        fprintf(stderr, "Error executing command: %s\n", command);
    }
}

/*
 * "Safe" wrapper around apache_strdup().
 */
static char *
apache_strdup(const char *in)
{
        char       *tmp;

        if (!in)
        {
                fprintf(stderr,
                                ("cannot duplicate null pointer (internal error)\n"));
                exit(EXIT_FAILURE);
        }
        tmp = strdup(in);
        if (!tmp)
        {
                fprintf(stderr, ("out of memory\n"));
                exit(EXIT_FAILURE);
        }
        return tmp;
}

