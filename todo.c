#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"


int main(int argc, char const *argv[])
{
	char filename[] = "tasks.txt";

	// If just 'todo' then list the available options
	if(argc == 1 )
	{
		printf("Options: ");
		printf("add, check, list");
	}
	// If 'todo add'
	else if(strcmp("add", argv[1]) == 0)
    {
    	// Get cmd line arguments
    	// Starts at argv[2]
    	// argv[2] will designate the type of task
    	if(argc > 8) // <--- Maximum of 5 tasks (argv[0] is todo, argv[1] is add, argv[2] is type)
    	{
    		printf("Too many tasks!");
    	}
    	else if(argc == 2)
    	{
    		printf("Usage: todo add [type] [task1] [task2] ... [task5]\n");
    		printf("Maximum of 5 tasks\n");
    	}
    	else
    	{
    		char type[50]; // Holds the type
    		strcpy(type, argv[2]);
    		char tasks[5][100];
    		printf("Type is: %s\n\n", type);
    		if(argc < 4)
    		{
				printf("No tasks entered!\n");
    	    	 			
    		}
    		else
    		{
    			// Open file for appending
    			FILE *file;
    			file = fopen(filename, "r+"); // Assume files exists
    			int num_tasks;

    			if(file == NULL) // Goes here if the file doesn't exist yet
    			{
    				file = fopen(filename, "w+");
    				fprintf(file, "%d\n\n", 0); // Initializes db to have 0 tasks.
    				num_tasks = 0;
    				fprintf(file, "%s\t%s\t%s\n", "id#", "Type", "Tasks");
    				printf("Making your todo list... Number of tasks : %d\n", num_tasks);
    			}
    			else
    			{
    				fscanf(file, "%d", &num_tasks); // Get the total number of tasks
    				printf("Number of tasks is : %d\n", num_tasks);
    			}

    			// Puts the tasks inside the tasks array to be appended to the file

    			int id;
    			for(int i = 3; i < argc; i++)
    			{
    				strcpy(tasks[i-3], argv[i]);

    				id = num_tasks + 1;
    				num_tasks++;
    				fprintf(file, "%d\t%s\t%s\n", id, argv[2], tasks[i-3]);
    				printf("Entered task: %s\n", tasks[i-3]);
    			} 
    			// The first line of the file contains the amount of tasks

    			fseek(file, 0, SEEK_SET); // Puts pointer back to the start of the file
    			fprintf(file, "%d", num_tasks); // Updates number of tasks

    			fclose(file);


    		}
  		
    	}


    }
	// If 'todo x'
    else if(strcmp("check", argv[1]) == 0)
    {
    	if(argc == 2)
    	{
    		
    	}
    }
	// If 'todo list'
    else if(strcmp("list", argv[1]) == 0)
    {
    	FILE *file;
    	file = fopen(filename, "r"); // Opens file for reading
    	int num_tasks;
    	if(file == NULL)
    	{
    		printf("No tasks yet. Add files with `todo add`\n");
    	}
    	else
    	{
    		fscanf(file, "%d", &num_tasks); // Get the total number of tasks
    		if(num_tasks == 0)
    		{
    			printf("No tasks yet. Add files with `todo add`\n");
    		}
    		else
    		{
    			char garbage[200];
    			int id;
    			char type[50];
    			char desc[100];

    			// This section skips to the actual data
    			fgets(garbage, 5, file);
    			fgets(garbage, 5, file);
    			fscanf(file, "%s\t%s\t%s\n", garbage, garbage, garbage);
    			strcpy(garbage, "");

    			printf("Number of tasks to complete: %d\n\n", num_tasks);
				printf("Tasks you gotta do!!\n\n");
				printf("id#\tType\tDescription\n");
				printf("---\t-----\t-----------\n");

    			// Read line by line and printf that bitch.
    			while(file != NULL && (feof(file)) == 0)
    			{
					fscanf(file, "%d\t%s\t%s\n", &id, type, desc);
					printf("%d\t%s\t%s\n", id, type, desc);
					// Clear char arrays
					strcpy(type, "");
					strcpy(desc, "");
    			}

    			fclose(file);

    		}
    	}
    }


	return 0;

}