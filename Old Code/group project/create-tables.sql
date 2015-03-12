create table supplier (
    name varchar(100) not null,
    addr varchar(255) not null,
    primary key (name)
) type = innodb;

create table supplierPhone (
    phoneNo varchar(20) not null,
    supName varchar(100) not null,
    primary key (phoneNo),
    index name_ind (supName),
    foreign key (supName) references supplier(name)
) type = innodb;

create table orders (
    idNo int unsigned not null auto_increment,
    supName varchar(100) not null,
    datePlaced date not null,
    primary key (idNo),
    index name_ind (supName),
    foreign key (supName) references supplier(name)
) type = innodb;

create table part (
    idNo int unsigned not null auto_increment,
    price decimal(19,4) not null,
    descr text,
    stock int unsigned not null,
    primary key (idNo),
    index id_ind (idNo)
) type = innodb;

create table op (
    pIdNo int unsigned not null,
    oIdNo int unsigned not null,
    quantity int unsigned not null,
    unitPrice decimal(19,4) not null,
    primary key (pIdNo, oIdNo),
    index pid_ind (pIdNo),
    index oid_ind (oIdNo),
    foreign key (pIdNo) references part(idNo),
    foreign key (oIdNo) references orders(idNo) on delete cascade
) type = innodb;

create table yexpenses (
    year int not null,
    rent decimal(19,4) not null,
    primary key (year)
) type = innodb;

create table mexpenses (
    month tinyint not null,
    year int not null,
    heat decimal(19,4) not null,
    water decimal(19,4) not null,
    electric decimal(19,4) not null,
    primary key (month, year),
    index yr_ind (year),
    foreign key (year) references yexpenses(year)
) type = innodb;

create table car (
    idNo int unsigned not null auto_increment,
    plate varchar(7) not null,
    province char(2) not null,
    make varchar(32),
    model varchar(32),
    ctype varchar(32),
    year int,
    color varchar(32),
    primary key (idNo),
    index mk_ind (make),
    index ml_ind (model),
    unique (plate, province)
) type = innodb;

create table customer (
    custNo int unsigned not null auto_increment,
    fname varchar(100),
    lname varchar(100),
    addr varchar(255) not null,
    hphone varchar(20),
    wphone varchar(20),
    primary key (custNo),
    index fn_ind (fname),
    index ln_ind (lname),
    index hp_ind (hphone),
    index wp_ind (wphone)
) type = innodb;

create table carPurchase (
    idNo int unsigned not null,
    custNo int unsigned not null,
    buyDate date not null,
    buyPrice decimal(19,4) not null,
    primary key (idNo, custNo),
    index id_ind (idNo),
    index cid_ind (custNo),
    foreign key (idNo) references car(idNo),
    foreign key (custNo) references customer(custNo)
) type = innodb;

create table carForSale (
    idNo int unsigned not null,
    serial int not null,
    km int not null,
    salePrice decimal(19,4) not null,
    primary key (idNo),
    index id_ind (idNo),
    foreign key (idNo) references carPurchase(idNo),
    index km_ind (km),
    index pr_ind (salePrice)
) type = innodb;

create table carForSaleRepairs (
    idNo int unsigned not null,
    cost decimal(19,4) not null,
    repDate date not null,
    primary key (idNo, repDate),
    index id_ind (idNo),
    foreign key (idNo) references carForSale(idNo)
) type = innodb;

create table repair (
    transNo int unsigned not null auto_increment,
    idNo int unsigned not null,
    custNo int unsigned not null,
    cost decimal(19,4) not null,
    transDate date not null,
    primary key (transNo),
    index id_ind (idNo),
    index cid_ind (custNo),
    foreign key (idNo) references car(idNo),
    foreign key (custNo) references customer(custNo)
) type = innodb;

create table employee (
    empNo int unsigned not null,
    sin char(9) not null,
    jobDesc text not null,
    startDate date not null,
    endDate date,
    unique (sin),
    index eid_ind (empNo),
    foreign key (empNo) references customer(custNo)
) type = innodb;

create table carSold (
    dateSold date not null,
    idNo int unsigned not null,
    custNo int unsigned not null,
    empNo int unsigned not null,
    serial int,
    sellPrice decimal(19,4) not null,
    primary key (dateSold, idNo),
    index id_ind (idNo),
    index cid_ind (custNo),
    index eid_ind (empNo),
    foreign key (idNo) references car(idNo),
    foreign key (custNo) references customer(custNo),
    foreign key (empNo) references employee(empNo)
) type = innodb;

create table HREmployee (
    empNo int unsigned not null,
    curRate decimal(19,4) not null,
    primary key (empNo),
    index cid_ind (empNo),
    foreign key (empNo) references employee(empNo)
) type = innodb;

create table HREhoursWorked (
    empNo int unsigned not null,
    workDate date not null,
    hours tinyint unsigned not null,
    primary key (empNo, workDate),
    index eid_ind (empNo),
    foreign key (empNo) references HREmployee(empNo)
) type = innodb;

create table HREpastRates (
    empNo int unsigned not null,
    beginDate date not null,
    endDate date not null,
    payRate decimal(19,4) not null,
    index eid_ind (empNo),
    foreign key (empNo) references HREmployee(empNo)
) type = innodb;

create table ASEmployee (
    empNo int unsigned not null,
    curSalary decimal(19,4) not null,
    primary key (empNo),
    index eid_ind (empNo),
    foreign key (empNo) references employee(empNo)
) type = innodb;

create table ASEpastSalaries (
    empNo int unsigned not null,
    year int not null,
    salary decimal(19,4) not null,
    primary key (empNo, year),
    index eid_ind (empNo),
    foreign key (empNo) references ASEmployee(empNo)
) type = innodb;
