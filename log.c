#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "log.h"

FILE* Log_fp = NULL;

bool OpenLog ()
{
	char log_file [ LOGNAMEMAX ];
	struct tm tm;
	time_t now_time = time ( NULL );
	localtime_r ( &now_time, &tm );

	if ( Log_fp != NULL ) CloseLog ();	// ファイルポインタがNULLでなかったら

	sprintf ( log_file, // 出力先ポインタ
			  "%s/%s_%04d%02d%02d%02d%02d%02d.log", // 出力形式フォーマット
			  LOGROOT,
			  LOGBASENAME, // ログファイルベースネーム
			  tm.tm_year + 1900,
			  tm.tm_mon + 1,
			  tm.tm_mday,
			  tm.tm_hour,
			  tm.tm_min,
			  tm.tm_sec );

	Log_fp = fopen ( log_file, "a+");

	return Log_fp;
}

void WriteLog ( bool eflag, char* format, ... )
{
	struct tm tm;
	time_t now_time = time ( NULL );
	localtime_r ( &now_time, &tm );
	va_list arg_list;

	if ( Log_fp == NULL ) return;

	va_start ( arg_list, format );
	fprintf ( Log_fp, "%02d:%02d:%02d | ", tm.tm_hour, tm.tm_min, tm.tm_sec );
	if ( eflag )
	{
		fprintf ( Log_fp, "[ FAIL ] " );
	}
	else
	{
		fprintf ( Log_fp, "[  OK  ] " );
	}
	vfprintf ( Log_fp, format, arg_list );
	fprintf ( Log_fp, "\n" );
	va_end ( arg_list );
}

void CloseLog ( )
{
	if ( Log_fp != NULL )
	{
		fclose ( Log_fp );
		Log_fp = NULL;
	}
}