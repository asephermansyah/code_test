#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int parse_comma_delimited_str(char *string, char **fields, int max_fields);
int SetTime(char *date, char *time);
int SetPosition(char *latitude, char *longitude);
struct tm gpstime;
double latitude_pos, longitude_pos;

int main(void){
    char buffer[255];
    int i;
	char *field[20];

    //read the input.nmea file
    FILE * fp;
    fp = fopen ("input.nmea", "r");
    
    if(fp == NULL) {
      perror("Error opening file");
      return(-1);
    }

    //parse the input data
    while( fgets (buffer, sizeof(buffer), fp)!=NULL ) {

    if ((strncmp(buffer, "$GP", 3) == 0) |
				(strncmp(buffer, "$GN", 3) == 0)) {

						if (strncmp(&buffer[3], "GGA", 3) == 0) {
							i = parse_comma_delimited_str(buffer, field, 20);
							
                            SetPosition(field[2],field[4]);
						}
						if (strncmp(&buffer[3], "RMC", 3) == 0) {
							i = parse_comma_delimited_str(buffer, field, 20);
							
							SetTime(field[9],field[1]);
						}
                }

    //print the output to console all of the NMEA string inside the input.nmea
	printf("Latitude  :%f\r\n",latitude_pos);
	printf("Longitude :%f\r\n",longitude_pos);
	printf("UTC Time  :%02d:%02d:%02d\r\n",gpstime.tm_hour, gpstime.tm_min, gpstime.tm_sec);
	printf("Date      :%02d-%02d-%02d\r\n\n",gpstime.tm_mday,(gpstime.tm_mon)+1,(gpstime.tm_year)%100);

    }

    fclose(fp);

    return 0;
}

int parse_comma_delimited_str(char *string, char **fields, int max_fields)
{
	int i = 0;
	fields[i++] = string;

	while ((i < max_fields) && NULL != (string = strchr(string, ','))) {
		*string = '\0';
		fields[i++] = ++string;
	}

	return --i;
}

int SetPosition(char *latitude, char *longitude)
{
    char temp_degrees[2];
    char temp_minutes[6];
    double lat_minutes, long_minutes, lat_degrees, long_degrees;;
    
    //Parse latitude degrees
    strncpy(temp_degrees, (char *)latitude, 2);
    temp_degrees[2] = '\0';
	lat_degrees = atof(temp_degrees);

    //Parse latitude minutes
    strncpy(temp_minutes, (char *)latitude+2, 6);
	lat_minutes = atof(temp_minutes);

    //Parse longitude degrees
    strncpy(temp_degrees, (char *)longitude, 3);
	long_degrees = atof(temp_degrees);

    //Parse longitude minutes
    strncpy(temp_minutes, (char *)longitude+3, 6);
	long_minutes = atof(temp_minutes);

    latitude_pos = lat_degrees + lat_minutes/60;
    longitude_pos = long_degrees + long_minutes/60;
}

int SetTime(char *date, char *time)
{
	//time_t secs;
	char tempbuf[2];

	// printf("GPS    UTC_Date %s, UTC_Time %s\r\n",date, time);
	// GPS date has format of ddmmyy
	// GPS time has format of hhmmss.ss

	if ((strlen(date) != 6) | (strlen(time) != 10)) {
		printf("No date or time fix. Exiting\r\n");
		return 1;
	}

	// Parse day:
	strncpy(tempbuf, (char *)date, 2);
	tempbuf[2] = '\0';
	gpstime.tm_mday = atoi(tempbuf);

	// Parse month:
	strncpy(tempbuf, (char *)date+2, 2);
	tempbuf[2] = '\0';
	gpstime.tm_mon = atoi(tempbuf) - 1;

	// Parse year:
	strncpy(tempbuf, (char *)date+4, 2);
	tempbuf[2] = '\0';
	gpstime.tm_year = atoi(tempbuf) + 100;

	// Parse hour:
	strncpy(tempbuf, (char *)time, 2);
	tempbuf[2] = '\0';
	gpstime.tm_hour = atoi(tempbuf);

	// Parse minutes:
	strncpy(tempbuf, (char *)time+2, 2);
	tempbuf[2] = '\0';
	gpstime.tm_min = atoi(tempbuf);

	// Parse seconds:
	strncpy(tempbuf, (char *)time+4, 2);
	tempbuf[2] = '\0';
	gpstime.tm_sec = atoi(tempbuf);

}