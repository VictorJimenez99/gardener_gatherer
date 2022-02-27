drop table if exists rack;
create table rack(
     id integer primary key not null default 0,
     total_slots integer not null default 0,
     available_slots integer not null default 0,
     description text not null default 'without-description'
);


drop table if exists plant;
create table plant(
    id integer primary key not null default 0,
    rack integer not null default 0,
    rack_position integer not null default 0,
    species text not null default 'UNKNOWN',
    status integer not null default 0,
    constraint plant_rack_fk
                  foreign key (rack) references rack(id)
                  on delete cascade on update restrict
);



