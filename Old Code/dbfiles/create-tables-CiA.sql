create table member (
    memNo int unsigned not null auto_increment,
    fname varchar(100),
    lname varchar(100),
    addr varchar(255) not null,
    hphone varchar(20),
    wphone varchar(20),
    primary key (memNo)
);

