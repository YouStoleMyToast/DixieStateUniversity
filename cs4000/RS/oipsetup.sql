//////////////////////////////////////////////////////////////////////////////////
drop table if exists oipmembers;
create table oipmembers(username varchar(20) not null, clanrank varchar(20), location varchar(30),competing tinyint(1), lastcap varchar(20), primary key (username));


insert into oipmembers values(username, clanrank, competing, lastcap);

delete from  oipmembers where username='   ';

insert into oipmembers (username, clanrank, competing) values
('Alys Tots','Swabbie',1),('Amander','Swabbie',1),('Angel 0140','Swabbie',1),('Availhunter','Swabbie',1),('Bloozero12','Swabbie',1),('Cdandria','Swabbie',1),
('Corrupt3d X','Swabbie',1),('Cutecavies','Swabbie',1),('D Turley','Swabbie',1),('DiegoVill','Swabbie',1),('Fine Madness','Swabbie',1),
('Kestra Akadi','Swabbie',1),('Killer5037','Swabbie',1),('Koll 100','Swabbie',1),('Koolgirl 11','Swabbie',1),('Kubrat Dulo','Swabbie',1),
('Lady Binks','Swabbie',1),('Lord Crogg','Swabbie',1),('Lotta Snow','Swabbie',1),('Mamavanna','Swabbie',1),('Marvel A','Swabbie',1),
('Mavortius','Swabbie',1),('Maybe Joe','Swabbie',1),('Nexus Pyro','Swabbie',1),('Ninja of OIP','Swabbie',1),('Nymph ryder','Swabbie',1),
('OIP bahar','Swabbie',1),('Oak Island','Swabbie',1),('Open4biz','Swabbie',1),('Open4s Mrs','Swabbie',1),('Owl Hoot64','Swabbie',1),
('Rebel Ry','Swabbie',1),('Ribjob','Swabbie',1),('Risita','Swabbie',1),('SensesFelt','Swabbie',1),('Shiro Hyou','Swabbie',1),
('Sion Wilder','Swabbie',1),('Sir Taldur','Swabbie',1),('Skc John','Swabbie',1),('Squirkey7','Swabbie',1),('Sylph Angel','Swabbie',1),
('True bl00d','Swabbie',1),('Tyler of OIP','Swabbie',1),('Will dabeast','Swabbie',1),('Wuy21','Swabbie',1),('Z Dude83','Swabbie',1),
('evenchoice','Swabbie',1),('iDovotchka','Swabbie',1),('roo dog','Swabbie',1),('scottieBotie','Swabbie',1),('xzarahsx','Swabbie',1),('ystogan','Swabbie',1);

//////////////////////////////////////////////////////////////////////////////////
drop table if exists apr2013a;
create table apr2013a(username varchar(20) not null, skill varchar(20) not null, initlevel  int not null, initxp int not null, finlevel  int not null, finxp int not null, diflevel  int not null, difxp int not null);

Insert into apr2013a values(username, skill, initlevel, initxp);

update apr2013a set finlevel='  '   and finxp='   '   where username='   ';

update apr2013a set diflevel=finlevel-initlevel and difxp=finxp-initxp where username='   '; 


//////////////////////////////////////////////////////////////////////////////////
drop table if exists runeskills;
create table runeskills(skillnum varchar(20) not null, skill varchar(20) not null, primary key (skillnum));

insert into runeskills values($skill);

//////////////////////////////////////////////////////////////////////////////////
create table runeranks(rank_id int(2) not null, rank varchar(20) not null, primary key(rank_id));

insert into runeranks values(1,'Council'),(2,'Swashbuckler'),(3,'Buccaneer'),(4,'Privateer'),(5,'Swabbie'),(6,'Landlubber'),(7,'Friendly Port'),(8,'Stowaway');

//////////////////////////////////////////////////////////////////////////////////
drop table if exists runegames;
create table runegames(minigame varchar(20) not null, primary key (minigame));

insert into runegames values($minigame);




//////////////////////////////////////////////////////////////////////////////////
drop table if exists runeitems;
create table runeitems(itemname varchar(20) not null, description varchar(20), currprice varchar(20) , primary key (itemname));

insert into runeitems($itemname, $description, $currprice);

//////////////////////////////////////////////////////////////////////////////////
insert into runeskills values(1,'Overall'),(2,'Attack'),(3,'Defence'),(4,'Strength'),(5,'Constitution'),(6,'Ranged'),(7,'Prayer'),(8,'Magic'),(9,'Cooking'),(10,'Woodcutting'),(11,'Fletching'),(12,'Fishing'),(13,'Firemaking'),(14,'Crafting'),(15,'Smithing'),(16,'Mining'),(17,'Herblore'),(18,'Agility'),(19,'Thieving'),(20,'Slayer'),(21,'Farming'),(22,'Runecrafting'),(23,'Hunter'),(24,'Construction'),(25,'Summoning'),(26,'Dungeoneering');
//////////////////////////////////////////////////////////////////////////////////
create table ninetynine(username varchar(30) not null, skill varchar(30) not null, primary key(username,skill));
create table runemax(username varchar(30) not null);

create table oipmembers(username varchar(30) not null, clanrank varchar(30), competitive tinyint(1), lastcap varchar(20),overallrank int(20),overalllevel int(20),overallxp int(20),attackrank int(20),attacklevel int(20),attackxp int(20),defencerank int(20),defencelevel int(20),defencexp int(20),strengthrank int(20),strengthlevel int(20),strengthxp int(20),constitutionrank int(20),constitutionlevel int(20),constitutionxp int(20),rangedrank int(20),rangedlevel int(20),rangedxp int(20),prayerrank int(20),prayerlevel int(20),prayerxp int(20),magicrank int(20),magiclevel int(20),magicxp int(20),cookingrank int(20),cookinglevel int(20),cookingxp int(20),woodcuttingrank int(20),woodcuttinglevel int(20),woodcuttingxp int(20),fletchingrank int(20),fletchinglevel int(20),fletchingxp int(20),fishingrank int(20),fishinglevel int(20), fishingxp int(20),firemakingrank int(20),firemakinglevel int(20),firemakingxp int(20),craftingrank int(20),craftinglevel int(20),craftingxp int(20),smithingrank int(20),smithinglevel int(20),smithingxp int(20),miningrank int(20),mininglevel int(20),miningxp int(20),herblorerank int(20),herblorelevel int(20),herblore int(20),agilityrank int(20),agilitylevel int(20),agilityxp int(20),thievingrank int(20),thievinglevel int(20),thievingxp int(20),slayerrank int(20),slayerlevel int(20),slayerxp int(20),farmingrank int(20),farminglevel int(20),farmingxp int(20),runecraftingrank int(20),runecraftinglevel int(20),runecraftingxp int(20),hunterrank int(20),hunterlevel int(20),hunterxp int(20),constructionrank int(20),constructionlevel int(20),constructionxp int(20),summoningrank int(20),summoninglevel int(20),summoningxp int(20),dungeoneeringrank int(20),dungeoneeringlevel int(20),dungeoneeringxp int(20), primary key(username));
insert into oipmembers values($username, $clanrank, 1, null, $statlist[0],$statlist[1],$statlist[2],$statlist[3],$statlist[4],$statlist[5],$statlist[6],$statlist[7],$statlist[8],$statlist[9],$statlist[10],$statlist[11],$statlist[12],$statlist[13],$statlist[14],$statlist[15],$statlist[16],$statlist[17],$statlist[18],$statlist[19],$statlist[20],$statlist[21],$statlist[22],$statlist[23],$statlist[24],$statlist[25],$statlist[26],$statlist[27],$statlist[28],$statlist[29],$statlist[30],$statlist[31],$statlist[32],$statlist[33],$statlist[34],$statlist[35],$statlist[36],$statlist[37],$statlist[38],$statlist[39],$statlist[40],$statlist[41],$statlist[42],$statlist[43],$statlist[44],$statlist[45],$statlist[46],$statlist[47],$statlist[48],$statlist[49],$statlist[50],$statlist[51],$statlist[52],$statlist[53],$statlist[54],$statlist[55],$statlist[56],$statlist[57],$statlist[58],$statlist[59],$statlist[60],$statlist[61],$statlist[62],$statlist[63],$statlist[64],$statlist[65],$statlist[66],$statlist[67],$statlist[68],$statlist[69],$statlist[70],$statlist[71],$statlist[72],$statlist[73],$statlist[74],$statlist[75],$statlist[76],$statlist[77],$statlist[78])
$memquery="insert into oipmembers values('".$username."','".$clanrank."','1', 'null','".$statlist[0]."','".$statlist[1]."','".$statlist[2]."','".$statlist[3]."','".$statlist[4]."','".$statlist[5]."','".$statlist[6]."','".$statlist[7]."','".$statlist[8]."','".$statlist[9]."','".$statlist[10]."','".$statlist[11]."','".$statlist[12]."','".$statlist[13]."','".$statlist[14]."','".$statlist[15]."','".$statlist[16]."','".$statlist[17]."','".$statlist[18]."','".$statlist[19]."','".$statlist[20]."','".$statlist[21]."','".$statlist[22]."','".$statlist[23]."','".$statlist[24]."','".$statlist[25]."','".$statlist[26]."','".$statlist[27]."','".$statlist[28]."','".$statlist[29]."','".$statlist[30]."','".$statlist[31]."','".$statlist[32]."','".$statlist[33]."','".$statlist[34]."','".$statlist[35]."','".$statlist[36]."','".$statlist[37]."','".$statlist[38]."','".$statlist[39]."','".$statlist[40]."','".$statlist[41]."','".$statlist[42]."','".$statlist[43]."','".$statlist[44]."','".$statlist[45]."','".$statlist[46]."','".$statlist[47]."','".$statlist[48]."','".$statlist[49]."','".$statlist[50]."','".$statlist[51]."','".$statlist[52]."','".$statlist[53]."','".$statlist[54]."','".$statlist[55]."','".$statlist[56]."','".$statlist[57]."','".$statlist[58]."','".$statlist[59]."','".$statlist[60]."','".$statlist[61]."','".$statlist[62]."','".$statlist[63]."','".$statlist[64]."','".$statlist[65]."','".$statlist[66]."','".$statlist[67]."','".$statlist[68]."','".$statlist[69]."','".$statlist[70]."','".$statlist[71]."','".$statlist[72]."','".$statlist[73]."','".$statlist[74]."','".$statlist[75]."','".$statlist[76]."','".$statlist[77]."','".$statlist[78]."')";
			