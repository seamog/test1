#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_LOG_BUF		1024
#define MAX_LOG_PATH	1024

int		g_log_file_size = 0;
char	g_wlog_path[MAX_LOG_PATH]="../log";			/* internal log */

void
wlog(char *fmt, ... )
{
	va_list args;
	char buff[MAX_LOG_BUF], buf[MAX_LOG_BUF];
	char filename[MAX_LOG_PATH];
	time_t sys_time;
	struct tm *date;
	static int handle = 0;
	static int day = 0;

	va_start( args, fmt );
	vsprintf( buff, fmt, args );
	va_end( args );

	/* time( &sys_time ); */
	sys_time = time(0);
	date = localtime( &sys_time );

	sprintf( buf, "[%02d:%02d:%02d] %s\n", date->tm_hour, date->tm_min, date->tm_sec, buff );

	if (day == 0 || day != date->tm_mday)
	{
		if (handle)	close(handle);

		sprintf (filename, "%s/OTP.%04d%02d%02d", g_wlog_path, date->tm_year + 1900, date->tm_mon+1, date->tm_mday);

		if( (handle = open( filename, O_RDWR|O_APPEND|O_CREAT, 0666)) < 0 )
		{
			fprintf (stderr, "LogFile(%s) Open Error!!\n", filename);
			return;
		}
		day = date->tm_mday;
	}

	write (handle, buf, strlen(buf));
}

