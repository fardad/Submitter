# Submitter
<h3>A program to help submit student work on a Linux server</h3>
written by Fardad Soleimanloo updated January 2022
  
[Click here to go to installation instructions](#installation-instructions-at-seneca)

## What is Submitter?

The submitter application helps students check and submit their assignment solutions in a unified way in a Linux environment by automating compilation, program output verification and submission, and thereby removing some of the marking tasks from the professor's responsibility.

This application replaces the traditional assignment submission process in console programming courses at Seneca. The traditional submission process can be summarized as follows.

- The assignment description was published for the students, possibly with some initial code to help them start their work.
- The students would follow the instructions in the assignment and complete its tasks. They would do this either on Matrix (the Linux platform in Seneca) or locally on a computer and then upload their solution to Matrix.
- The students were asked to somehow capture the output of their program by redirecting the output to a text file or by recording the execution process using a typescript command.
- The student would upload or attach the source code or the typescript to an email for their professor to mark. 

There was no guarantee that the source code attached was actually the code that generated the output, that the compilation process was genuinely successful or that the typescript was not modified manually to match the expected output.

Under this system, it was the student’s responsibility to ensure that the output is EXACTLY as expected with no immediate feedback. The professor would verify this at marking time and any errors would cost the student a significant portion of the total possible mark. The student would learn from their mistake, days and sometimes weeks, after submitting the assignment and receiving their mark.

The submitter application described in this note notifies the students of any errors in the compilation or execution phases enabling them to correct their solutions before submitting them to the professor. The application also ensures that the output submitted is produced by the source code submitted.


### How does it work?

The submitter program is a C++ program written to execute Linux commands based on a configuration file created separately for each assignment. The template for this file is created in the proper directory by the installation script.

The professor installs the submitter program in their home directory on a Linux platform that the students will use to submit their assignments. Professors then create a configuration file for each (deliverable) assignment in the configuration directory of the Submitter application.

This file tells the Submitter program how to process each student's solution before emailing it to the professor's account.

Each student submits their solution by running the submitter program installed in the professor's directory.

For example, if Professor **John Doe** wants his students to use the Submitter application for **Workshop 2** of **OOP244** subject and the configuration file he created for this is located in the **"244"** directory under the name **"w2.cfg"**, his students should issue this command to submit their Workshop 2 on matrix from their working directory:

```shell
$ ~john.doe/submit 244/w2<ENTER>
```

#### Students with accommodation

To give extra time to students with accommodation or occasionally give extensions to individual students for any reason, you can add exceptions to an accommodation configuration file for individual students and the submitter application will automatically apply the extensions to those individuals.

### Installation Instructions (at Seneca)
First, the professor needs to install the program; this is how it is done:

Login to your account on Matrix 
> if your account is not activated, email `helpdesk(at)senecacollege.ca` requesting to activate your account.

In your home directory, enter the following commands:

```shell
$ git clone https://github.com/fardad/Submitter.git
$ cd Submitter
$ chmod 700 install
$ install
```
and done!

These commands do the following:

- Create a directory called “Submitter” and download the installation script and all of the
source files from GitHub.
- Change the current directory to the “Submitter” directory
- Give execute permission to the installation script
- install the submitter

During the installation process, the following will happen:

- You will be prompted with a warning that access to your root directory will be modified to 711. 
> Make sure that the sub-directories of your home directory have the proper permissions so that they are not exposed by this modification 

- The install script will then compile the source code and create a sub-directory called submitter_files in your home directory.
- The submitter executable (the submit command) will be copied to the root of the account with proper permissions. 
- The submitter_files directory will include the submission configuration template file (`template.cfg`).  This directory is where all the files for the submitter program are stored.
- If you are reinstalling the submitter, you might get errors for already existing directories and files. You can ignore these messages.

once the installation script finishes executing, the Submitter application is ready to configure for a particular assignment.

### Configuration Instructions

Let us assume that we are preparing Workshop 5 and that we want our students to use the following command to compile their code:

```shell
$ g++ -Wall -std=c++11x -g -o w5exe w5.cpp w5main.cpp <ENTER>
```

And use a file called **w5data.csv** as a data file for their workshop

Since we are on a Linux system I rather call the executable “w5exe” and not “w5.exe”.

The values shown in bold below are values that we define in our configuration for this workshop.

Our first decision is the name of the configuration file. Let us say that we want the student to enter the following when they submit their assignment:
$ ~john.doe/submit 244/w5 <ENTER>

In this case, in the "submitter_files" directory there should be a directory called "244" and in there a file called: w5.cfg.

Then, we make a copy of template.cfg and save it in `submitter_files/244` under the name `w5.cfg1`:

$ cp submitter_files/template.cfg submitter_files/244/w5.cfg <ENTER>

We open ws5.cfg and provide the following information:

1. Administrative information:
    * Course code: Let’s say **OOP244**.
    * Professors user id: **john.doe**
    * Email to send the submissions to: **john.doe@senecacollege.ca**
    * Email of TA for feedback: **teacher.assist@senecacollege.ca** (If available)
    * Title of the workshop: **“Workshop 5”**
2. The files that must be present before the student can start the submission process:   
```w5.cpp,w5.h, w5.csv and reflect.txt```

3. Does this assignment need to be compiled: yes
    * The compile command without the source file names:
    ```g++ -Wall -std=c++11x -g -o w5exe```
    * The name of the executable that the compiler command generates: w5exe
    * The name of the files for unit testing (i.e. unit test program, data files, etc...): `w5main_prof.cpp., w5.csv`
        >if the assignment is going to be tested using a unit test or a main program that is handed out to the students. If this is the case the file for the unit test is saved in submitter_files/w5 to prevent a student from tempering with it  
    * The files that participate in the compilation command line:   
    ```w5.cpp, w5main_prof.cpp```
    * Are warnings allowed in the compilation: yes or no
    * The name of the file in which the compiler messages are captured: 
    ```errors.txt```
4. Is there a program to be executed for testing (does the output need to be validated):
    * Should a program be executed for testing: yes or no
    > If yes, you need to do the assignment yourself, test it, run it, capture the output and save it in a file for expected output. Let’s say the name of this file is `correct_output.txt`
    * The method of capturing the output – redirecting the output to a text file or
    creating a typescript. Let us choose typescript in this example: `script`
    * The name of the file that captures the execution result of the student's submission:
    ```correct_output.txt```
    * The comparison range (from line , to line , inclusive) , let’s say (5, 34). This means that only the output lines will be compared from line 5 to line 34, inclusive.
    * Should the student's output be compared to the expected output: **yes** or no
    * The name of the file with the expected output: `correct_output.txt`
5. The names of the files that the student needs to submit. Let’s say that these files are:
    ```w5.cpp,w5.h, w5.csv, w5main.cpp, reflect.txt```
    
Copying the values listed above into configuration file `244/w5.cfg` produces:

#### Sample config file

```text
-- Name and path of this file must be the same as the name and path you would 
-- like the students to use at the submission command;
--    if you like the submission command to be:
--    $ ~professorId/submit oop345A/ws/2<ENTER>
--    then this file should be copied under the name "2.cfg" in the
--    "sumbitter_files/oop345/ws" directory.
--    then for this submission you should modify its values base on your needs.

-- format for configuration values:
-- value_name|value1, value2, value3,...
-- all the values must be in the same line (you can not goto new line for values)
-- all the values below are examples and should change based on your subject



--Subject Code
  subject_code|OOP244

--Professor Linux userid
  userid|john.doe

--Professor and Teacher's assisstants emails
--you can add more emails to send a copy of submission to TAs
  prof_email|john.doe@senecacollege.ca, teacher.assist@senecacollege.ca, theta2@senecacollege.ca
  

--Assignment name
  assessment_name | Workshop 5

-- Announcement file name
-- format : announcement | filename
-- if not commented, looks for the "filename" in your submitter files directory
-- then copies the exact content at the begging of submission process
-- announcement | message.txt

-- Due dates and time, and thier titles 
-- You can have one or many due dates as long as they are coupled with their 
--     corresponding title
-- Format: due_dates | YYYY/MON/DAY-HH24:MIN, title1[, YYYY/MON/DAY-HH24:MIN, title2].... 
-- title 1 will be applied to the submissions between date one and two and title2 
-- will be applied to submissions between date two and three and etc...
-- the due date and time can be set,if the time is ommited it will be set to 23:59 

-- uncomment the line below to activate due date check
  due_dates|2021/1/11 , late(-30%), 2021/1/13, very late(-50%)

-- publication date
-- format: publish_date | YYYY/MON/DAY-HH24:MIN
-- submissions before this date will be rejected
-- but students can dry run the submission using -feedback option
-- uncomment the line below to activate the publication date check
-- publish_date | 2021/1/09

-- rejection date
-- format: rejection_date | YYYY/MON/DAY-HH24:MIN
-- sumbissions after this date and time are rejected.
-- uncomment the line below to activate the rejection date check
-- rejection_date | 2018/1/15 13:00


--files that must exist for a successful submission (or compile)
--   Submission is rejected if any of these file do not exist at the
--   current directory
  assess_files | w5.cpp, w5.h, w5.csv, w5main.cpp, reflect.txt
 

--File names and thier path to be copied to student account from professor's
--submitter files directory for testing (tester programs, data files and etc)
--comment out the line if you don't need copying
  copy_files|244/w5/w5main_prof.cpp,  244/w5/w5.csv


--The code will be compiled before submission if the value is yes
--compile code (yes, no)
  compile|yes


--compiler command
--if you want the program to be executed then this compile command should
--generate an exacutable with the same name as exe_name value (see next value)
  compile_command|g++ -Wall -std=c++11x -g -o w5exe


--executable name (must be the same as what the compiler command gererates)
  exe_name|  "valgrind -s --leak-check=full w5exe"


--files to compile (These files will be added to the compile at compile time
--this will be ignored if compile value is no
  compile_files|w5.cpp, w5main_prof.cpp


--error capture file name
--this file will hold the warnings and error resulted by compiling the code
  err_file|errors.txt

--Allow warnings in compilation (yes, no)
--If no is selected submission will be rejected
  allow_warning|no


--Execute the exe_name value after successful compilation
--execute (yes, no)
  execute|yes


--How to capture the output (script, redirect): 
--this will be ignored if check_output is no or execute is no)
--   "script", for interactive programs, typescript will be invoked
--   "redirect" or any other value, dump output to file for non-interactive programs
  output_type|script
	     
	     
--output file name
--the output of the execution or the typescript will be dumped in this
  output_file|student_output.txt



--compare the output to professor's; (yes, no)
--this will be ignored if execute value is no
--anything but "yes" will be considered as no value
--in this case the file for the output comparison should be copied to submitter_files dir.
--if skip_spaces exists and it is yes outputs will be checked for non space characters only 
--if the student chooses to do so by adding -skip_spaces to the submission command line
--if skip_blank_lines exists and it is yes outputs will be checked for non blank lines only 
--if the student chooses to do so by adding -skip_blank_lines to the submission command line
  check_output|yes 
  skip_spaces |yes
  skip_blank_lines |yes
  
  

--Check valgrind command output for memory leak
-- In case of valgrind output error messages the submission will be rejected only if
-- check_output is "yes"
--       To use this your exe_name must be : "valgrind -s --leak-check=full ws"
--       where ws is the generated executable by the compiler
--Possible values are yes, warn, no
--   yes, if there is memory leak it will not let the student submit code
--   warn, if there is memory lead it will warn the student but allows submission
--   no, or commenting check_valgrind will not check for memory leak
  check_valgrind|yes


--comparison range, line numbers and line numbers to skip comparison 
-- values: from, to , skip1, skip2; integer numbers
--to specify the range of comparison 
--(in this example lines 16 to line 31 (inclusive) will be compared skipping lines 20 and 24)
  comp_range|5, 34



--filename for the original output (correct output) in submitter_files dir.
--this will be ignored if check_output is no
  correct_output|correct_output.txt



--files to be emailed as submission. (if any of them is missing assingment 
--  can not be sumbitted)
--if commented the script will only test the output and nothing will be submitted.
  submit_files |whatever.cpp,whatever.h,reflect.txt

  
--CC (email) the submission to the student
--Commenting out these option is the same as a yes value
--"yes" and "no" are acceptable values
  CC_student|yes


--If CC_student is yes  
--  Attach the submitted files to the student confirmation email
--  Commenting out this option is the same as a yes value
  CC_student_files|yes


--Enforce submission location by adding accptable ip numbers
--by uncommenting this value and adding these sub ips you can inforce 
--the students' location:
--Format: 
--allowed_ips|Partial IP[,partial IP1]...
--for example the following restrict the submission to come from 
--anywhere from seneca: (allowed_ips|142.204. , 10.)
--to restrict submission from a lab computer at Seneca, find the ip of 
--one of the lab computers and add the first three numbers (ie. 10.23.34.)
--uncomment the following to activate location restriction
--allowed_ips|142.204. , 10.

```

#### Directory Structure

For the configuration to be complete, the “submitter_files” sub-directory must contain the directory 244/w5. With following files: 

- Config file: the file (`w5.cfg`) in the 244 directory
- Tester files: the two files (`w5.csv and w5main_prof.cpp`) in 244/w5 direcotry.
- Correct output file: file (`correct_output.txt`) in 244/w5 directory

#### Student Submission Instructions
##### Submission
To submit their solution, a student enters the following command:
```shell
$ ~john.doe/submit 244/w5 <ENTER>
```
* check and make sure that all the files needed are present
* compile the code with the provided tester main in the professor’s account
* prompt the students to get ready for demonstrating the execution of the assignment
* run the executable
* if done, compare the output generated with the expected output in the professor’s account
* If everything goes ok, attach all the files needed and email them to the professor and the TA.

If at any point, anything goes wrong, the submitter program will display a clear message to the student that identifies their mistake and prompt them to retry.

##### Due dates
Students can issue the following command to see the due date and times:
```shell
$ ~john.doe/submit 244/w5 -due<ENTER>
```
Submitter response:
```Text
System date and time: Sunday, 2021/1/11 - 18:17

Listing Workshop 3 «Part 1»  due dates:
Submissions are open after Saturday, 2021/01/09 - 23:59.
On-time submission before Monday, 2021/01/11 - 23:59
late(-30%) submission after Monday, 2021/02/11 - 23:59
very late(-50%) submission after Wednesday, 2021/02/13 - 23:59
Submissions are rejected after Friday, 2021/02/15 - 13:00!
```
##### Skipping spaces and lines
Student can submit their work (if the professor allows it in the config file) by 
adding -skip_spaces and/or -skip_lines to the submission command line.


