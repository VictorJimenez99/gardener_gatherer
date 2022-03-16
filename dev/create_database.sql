drop table if exists rack;
create table rack
(
    id              integer primary key not null default 0,
    total_rows      integer             not null default 1,
    total_columns   integer             not null default 1,
    available_slots integer             not null default -1,
    description     text                not null default 'without-description'
);

--  compute available slots after insertion (if null)
drop trigger if exists compute_available_rack_slots_after_rack_insert_trigger;
create trigger compute_available_rack_slots_after_rack_insert_trigger
    after insert
    on rack
    when new.available_slots = -1 /*Default value*/
begin
    update rack set available_slots = new.total_rows * new.total_columns where rowid = new.rowid;
end;


-- checks availability of slots before an update
drop trigger if exists check_available_rack_slots_before_update_rack_trigger;
create trigger check_available_rack_slots_before_update_rack_trigger
    before update
    on rack
begin
    select case
               when new.available_slots < 0
                   then raise(abort, 'Rack does not have available slots left') end;
end;

drop table if exists plant;
create table plant
(
    rack            integer not null default 0,
    rack_position_x integer not null default 0,
    rack_position_y integer not null default 0,
    species         text    not null default 'UNKNOWN',
    primary key (rack, rack_position_x, rack_position_y),
    constraint plant_rack_fk
        foreign key (rack) references rack (id)
            on delete cascade on update restrict
);

-- Check if new insert is in a valid position
drop trigger if exists check_rack_x_y_before_insert_plant_trigger;
create trigger check_rack_x_y_before_insert_plant_trigger
    before insert
    on plant
begin
    select case
               when (select total_rows from rack) < new.rack_position_x then
                   raise(abort, 'The system is trying to use a row that does not exist in the rack')
               when (select total_columns from rack) < new.rack_position_y then
                   raise(abort, 'The system is trying to use a column that does not exist in the rack')
               end;
end;

-- take slot after insertion
drop trigger if exists decrement_available_rack_slots_after_insert_plant_trigger;
create trigger decrement_available_rack_slots_after_insert_plant_trigger
    after insert
    on plant
begin
    update rack set available_slots = (available_slots - 1) where id = new.rack;
end;

-- return slot after removal
drop trigger if exists increment_available_rack_slots_after_delete_plant_trigger;
create trigger increment_available_rack_slots_after_delete_plant_trigger
    after delete
    on plant
begin
    -- we know that a plant can only be in a rack if it has enough space, so we don't need to check if
    -- this is giving back the slot is possible
    update rack set available_slots = (available_slots + 1) where id = old.rack;
end;

-- If a plant if moved from one rack to another recomputed the available slots in each one
drop trigger if exists recompute_available_rack_slots_after_plant_move_trigger;
create trigger recompute_available_rack_slots_after_plant_move_trigger
    after update of rack
    on plant
    when old.rack <> new.rack
begin
    update rack set available_slots = (available_slots + 1) where id = old.rack;
    update rack set available_slots = (available_slots - 1) where id = new.rack;
end;

-- Check if plant is being moved to a valid position
drop trigger if exists check_rack_x_y_before_update_plant_trigger;
create trigger check_rack_x_y_before_update_plant_trigger
    before update
    on plant
begin
    select case
               when (select total_rows from rack) < new.rack_position_x then
                   raise(abort, 'The system is trying to use a row that does not exist in the rack')
               when (select total_columns from rack) < new.rack_position_y then
                   raise(abort, 'The system is trying to use a column that does not exist in the rack')
               end;
end;


drop table if exists measurement;
create table measurement
(
    plant_rack  integer not null default 0,
    plant_x     integer not null default 0,
    plant_y     integer not null default 0,

    id          integer not null default 0,

    time        integer not null default 0,
    humidity    integer not null default 0,
    light       integer not null default 0,
    temperature real    not null default 0,

    primary key (plant_rack, plant_x, plant_y, id),

    constraint measurement_plant_fk
        foreign key (plant_rack, plant_y, plant_x) references
            plant (rack, rack_position_x, rack_position_y)
            on delete cascade on update restrict
);


drop trigger if exists update_id_after_insert_measurement_trigger;
create trigger update_id_after_insert_measurement_trigger
    after insert
    on measurement
begin
    update measurement set id = new.rowid where rowid = new.rowid;
end;


