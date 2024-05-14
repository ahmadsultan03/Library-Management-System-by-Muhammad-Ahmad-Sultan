show databases;
create database lms;
use lms;
SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


CREATE TABLE books (
  book_id int NOT NULL,
  name varchar(50) NOT NULL,
  publisher varchar(50) NOT NULL,
  edition varchar(30) NOT NULL,
  author varchar(30) NOT NULL
);

INSERT INTO books (book_id, name, publisher, edition, author) VALUES
(104, 'Sonnet', 'Thomas Thorpe ', '4th', 'Shakespear'),
(333, 'Java OOP', 'pearson', '3rd', 'Umair Javed'),
(700, 'Intro to Programming', 'Pearson', '4th', 'Paul Deitel, Harvey Deitel '),
(812, 'Paradise Lost', 'Samuel Simmons ', '3rd', 'John Milton');


CREATE TABLE issue (
  id int NOT NULL,
  book_id int NOT NULL,
  user_id int NOT NULL,
  issue_date varchar(20) NOT NULL
);

-- Dumping data for table `issue`
INSERT INTO issue (id, book_id, user_id, issue_date) VALUES
(4, 812, 157, 'Feb 14, 2018'),
(5, 104, 755, 'Feb 15, 2018');

-- Table structure for table `return_book`
CREATE TABLE return_book (
  id int NOT NULL,
  book_id int NOT NULL,
  user_id int NOT NULL,
  return_date varchar(30) NOT NULL
);

-- Dumping data for table `return_book`
INSERT INTO return_book (id, book_id, user_id, return_date) VALUES
(1, 812, 157, 'Feb 14, 2018'),
(2, 700, 638, 'Feb 19, 2018');

-- Table structure for table `student`
CREATE TABLE student (
  student_ID int NOT NULL,
  name varchar(30) NOT NULL,
  course varchar(20) NOT NULL,
  year varchar(20) NOT NULL,
  semester varchar(20) NOT NULL
);

-- Dumping data for table `student`
INSERT INTO student (student_ID, name, course, year, semester) VALUES
(157, 'ali', 'BBA', '1st', '1st'),
(638, 'adeel', 'BSCS', '2nd', '3rd'),
(755, 'anza', 'BSC', '2nd', '3rd');

-- Table structure for table `users`
CREATE TABLE users (
  id int NOT NULL,
  name varchar(40) NOT NULL,
  email varchar(40) NOT NULL,
  address varchar(50) NOT NULL,
  contact varchar(30) NOT NULL,
  password varchar(30) NOT NULL
);

-- Dumping data for table `users`
INSERT INTO users (id, name, email, address, contact, password) VALUES
(1, 'ahmad', 'ahmad@gmail.com', 'sahiwal ', '03061611301', '1122'),
(2, 'adnan', 'adnan@yahoo.com', 'mansehra', '03441231234', 'qwerty'),
(3, 'atiqa', 'atiqa777@gmail.com', 'rawalpindi', '03139998877', 'qwerty'),
(4, 'john', 'john@gmail.com', 'washington', '+923412343', '1234');

-- Indexes for dumped tables

-- Indexes for table `books`
ALTER TABLE books
  ADD PRIMARY KEY (book_id);

-- Indexes for table `issue`
ALTER TABLE issue
  ADD PRIMARY KEY (id),
  ADD KEY book_ID (book_id),
  ADD KEY user_ID (user_id);

-- Indexes for table `return_book`
ALTER TABLE return_book
  ADD PRIMARY KEY (id),
  ADD KEY book_id (book_id),
  ADD KEY user_id (user_id);

-- Indexes for table `student`
ALTER TABLE student
  ADD PRIMARY KEY (student_ID);

-- Indexes for table `users`
ALTER TABLE users
  ADD PRIMARY KEY (id);

-- AUTO_INCREMENT for dumped tables

-- AUTO_INCREMENT for table `issue`
ALTER TABLE issue
  MODIFY id int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
-- AUTO_INCREMENT for table `return_book`
ALTER TABLE return_book
  MODIFY id int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
-- AUTO_INCREMENT for table `users`
ALTER TABLE users
  MODIFY id int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

-- Constraints for dumped tables

-- Constraints for table `issue`
ALTER TABLE issue
  ADD CONSTRAINT book_ID FOREIGN KEY (book_id) REFERENCES books (book_id),
  ADD CONSTRAINT user_ID FOREIGN KEY (user_id) REFERENCES student (student_ID);

-- Constraints for table `return_book`
ALTER TABLE return_book
  ADD CONSTRAINT return_book_ibfk_1 FOREIGN KEY (book_id) REFERENCES books (book_id),
  ADD CONSTRAINT return_book_ibfk_2 FOREIGN KEY (user_id) REFERENCES student (student_ID);


select * from users;
select * from books;
select * from issue;
select * from return_book;
