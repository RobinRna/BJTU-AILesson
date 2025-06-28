-- MySQL dump 10.13  Distrib 9.0.1, for Win64 (x86_64)
--
-- Host: localhost    Database: airlinedb
-- ------------------------------------------------------
-- Server version	9.0.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `airline`
--

DROP TABLE IF EXISTS `airline`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `airline` (
  `airline_code` varchar(10) NOT NULL,
  `airline_name` varchar(100) NOT NULL,
  `contact_info` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`airline_code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `airline`
--

LOCK TABLES `airline` WRITE;
/*!40000 ALTER TABLE `airline` DISABLE KEYS */;
INSERT INTO `airline` VALUES ('CA','Air China','010-95583'),('MU','China Eastern','021-95530');
/*!40000 ALTER TABLE `airline` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `airlineflicount`
--

DROP TABLE IF EXISTS `airlineflicount`;
/*!50001 DROP VIEW IF EXISTS `airlineflicount`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `airlineflicount` AS SELECT 
 1 AS `airline_code`,
 1 AS `flight_count`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `airport`
--

DROP TABLE IF EXISTS `airport`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `airport` (
  `airport_code` varchar(10) NOT NULL,
  `airport_name` varchar(100) NOT NULL,
  `city` varchar(50) NOT NULL,
  `flight_zone` varchar(10) NOT NULL,
  PRIMARY KEY (`airport_code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `airport`
--

LOCK TABLES `airport` WRITE;
/*!40000 ALTER TABLE `airport` DISABLE KEYS */;
INSERT INTO `airport` VALUES ('PEK','Beijing Capital International Airport','Beijing','4F'),('PVG','Shanghai Pudong International Airport','Shanghai','4F');
/*!40000 ALTER TABLE `airport` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `flight`
--

DROP TABLE IF EXISTS `flight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `flight` (
  `flight_number` varchar(20) NOT NULL,
  `air_model` varchar(50) NOT NULL,
  `departure_time` datetime NOT NULL,
  `arrival_time` datetime NOT NULL,
  `departure_airport` varchar(10) NOT NULL,
  `arrival_airport` varchar(10) NOT NULL,
  `airline_code` varchar(10) NOT NULL,
  PRIMARY KEY (`flight_number`),
  KEY `departure_airport` (`departure_airport`),
  KEY `arrival_airport` (`arrival_airport`),
  KEY `airline_code` (`airline_code`),
  CONSTRAINT `flight_ibfk_1` FOREIGN KEY (`departure_airport`) REFERENCES `airport` (`airport_code`),
  CONSTRAINT `flight_ibfk_2` FOREIGN KEY (`arrival_airport`) REFERENCES `airport` (`airport_code`),
  CONSTRAINT `flight_ibfk_3` FOREIGN KEY (`airline_code`) REFERENCES `airline` (`airline_code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `flight`
--

LOCK TABLES `flight` WRITE;
/*!40000 ALTER TABLE `flight` DISABLE KEYS */;
INSERT INTO `flight` VALUES ('CA1112','Boeing737','2024-04-25 20:45:09','2024-04-25 23:45:09','PVG','PEK','CA'),('CA1234','Boeing737','2024-04-10 08:00:00','2024-04-10 10:30:00','PEK','PVG','CA'),('CA2849','Boeing737','2024-04-17 09:12:05','2024-04-17 13:12:05','PVG','PEK','CA'),('CA7836','Boeing737','2024-04-29 18:14:09','2024-04-29 22:14:09','PVG','PEK','CA'),('MU4241','AirbusA320','2024-04-29 17:01:06','2024-04-29 19:01:06','PVG','PEK','MU'),('MU5678','AirbusA320','2024-04-10 09:00:00','2024-04-10 11:45:00','PVG','PEK','MU'),('MU7290','AirbusA320','2024-04-15 07:43:00','2024-04-15 11:43:00','PVG','PEK','MU');
/*!40000 ALTER TABLE `flight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `flightsum`
--

DROP TABLE IF EXISTS `flightsum`;
/*!50001 DROP VIEW IF EXISTS `flightsum`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `flightsum` AS SELECT 
 1 AS `flight_number`,
 1 AS `departure_time`,
 1 AS `arrival_time`,
 1 AS `departure_airport_name`,
 1 AS `departure_city`,
 1 AS `arrival_airport_name`,
 1 AS `arrival_city`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary view structure for view `flighttime`
--

DROP TABLE IF EXISTS `flighttime`;
/*!50001 DROP VIEW IF EXISTS `flighttime`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `flighttime` AS SELECT 
 1 AS `flight_number`,
 1 AS `departure_time`,
 1 AS `arrival_time`,
 1 AS `flight_time`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `orderinfo`
--

DROP TABLE IF EXISTS `orderinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `orderinfo` (
  `order_id` int NOT NULL AUTO_INCREMENT,
  `id_card` varchar(20) NOT NULL,
  `moneys` decimal(10,2) NOT NULL,
  `payment` int NOT NULL,
  PRIMARY KEY (`order_id`),
  KEY `id_card` (`id_card`),
  CONSTRAINT `orderinfo_ibfk_1` FOREIGN KEY (`id_card`) REFERENCES `passenger` (`id_card`),
  CONSTRAINT `chk_payment` CHECK ((`payment` in (0,1)))
) ENGINE=InnoDB AUTO_INCREMENT=53 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orderinfo`
--

LOCK TABLES `orderinfo` WRITE;
/*!40000 ALTER TABLE `orderinfo` DISABLE KEYS */;
INSERT INTO `orderinfo` VALUES (1,'110101199001011234',1250.50,1),(2,'110101199002022345',3150.00,0),(3,'110101198810243608',2041.23,0),(4,'110101196803223943',1673.81,0),(5,'110101197507058250',2826.66,1),(6,'110101198411164376',539.77,1),(7,'110101195011276882',785.78,1),(8,'110101196909127547',1309.29,1),(9,'110101198610289070',2773.37,1),(10,'110101199506209367',711.23,1),(11,'110101198709081849',1567.04,1),(12,'110101199103086642',956.71,0),(13,'110101199806282974',1042.39,0),(14,'110101199602114217',2019.16,1),(15,'110101198909015468',998.95,1),(16,'110101199806092967',1221.80,1),(17,'110101195710268104',2595.06,1),(18,'110101196205083417',916.85,1),(19,'110101198908252802',2199.78,1),(20,'110101195902078356',1549.22,0),(21,'110101199407095228',2097.73,1),(22,'110101197702183195',2007.74,0),(23,'110101197212145297',892.12,0),(24,'110101195010215457',2662.74,1),(25,'110101199407142760',1268.23,1),(26,'110101199606058320',932.94,0),(27,'110101198910026821',1184.83,0),(28,'110101197404029144',1369.64,1),(29,'110101199806024063',1121.06,0),(30,'110101195405286187',851.51,0),(31,'110101199805127060',1239.58,0),(32,'110101196407104603',504.88,1),(33,'110101198610116271',2111.58,1),(34,'110101196009264879',1118.90,1),(35,'110101197401175503',2584.45,0),(36,'110101196010073093',1305.71,1),(37,'110101198208177794',2011.74,1),(38,'110101197011228296',1414.27,1),(39,'110101195603061279',1945.53,1),(40,'110101196206102759',1369.09,0),(41,'110101197204248910',2955.58,1),(42,'110101198306273248',2423.39,0),(43,'110101198312118306',1495.51,0),(44,'110101195510276691',1333.07,1),(45,'110101198908196586',2472.27,0),(46,'110101197607234259',734.69,0),(47,'110101198502083115',1954.95,0),(48,'110101195510198228',2737.81,1),(49,'110101197906032146',2454.11,1),(50,'110101199611172474',1487.88,0),(51,'110101197705159207',2171.31,1),(52,'110101198603093949',1924.43,1);
/*!40000 ALTER TABLE `orderinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `passenger`
--

DROP TABLE IF EXISTS `passenger`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `passenger` (
  `id_card` varchar(20) NOT NULL,
  `passname` varchar(50) NOT NULL,
  `age` int NOT NULL,
  `phone` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id_card`),
  CONSTRAINT `chk_age` CHECK (((`age` >= 0) and (`age` < 120)))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `passenger`
--

LOCK TABLES `passenger` WRITE;
/*!40000 ALTER TABLE `passenger` DISABLE KEYS */;
INSERT INTO `passenger` VALUES ('110101195010215457','Robin',42,'2130427306'),('110101195011276882','Rachel',50,'(695)853-1407x0976'),('110101195405286187','Mary',70,'572.245.9752x801'),('110101195510198228','Kimberly',28,'639.453.5941x8088'),('110101195510276691','Sheryl',68,'042.636.5506'),('110101195603061279','Patrick',42,'(746)521-7149x5387'),('110101195710268104','Matthew',57,'3250111485'),('110101195902078356','Angelica',39,'671.252.2284x988'),('110101196009264879','Candice',59,'+1-865-973-5344x0720'),('110101196010073093','Amber',38,'724.764.6974x6847'),('110101196205083417','Jillian',62,'001-037-770-3037x77578'),('110101196206102759','Belinda',41,'+1-922-270-8375x211'),('110101196407104603','Anthony',54,'001-461-627-5292'),('110101196803223943','Becky',41,'928.360.5914x489'),('110101196909127547','Scott',37,'001-153-608-6315'),('110101197011228296','Alexander',43,'011.380.8012x255'),('110101197204248910','Christopher',53,'+1-242-372-4582'),('110101197212145297','Jonathon',54,'001-403-902-1744x8060'),('110101197401175503','David',28,'843.438.0606'),('110101197404029144','Cynthia',65,'8588019068'),('110101197507058250','Erin',42,'267.199.0167x98313'),('110101197607234259','Cynthia',49,'001-136-356-1089'),('110101197702183195','Eric',25,'(955)463-7007x91646'),('110101197705159207','Tara',30,'(906)247-7268x7692'),('110101197906032146','Michael',69,'(774)996-3806'),('110101198208177794','Monica',69,'(759)453-6726x076'),('110101198306273248','Earl',23,'257-651-7307'),('110101198312118306','Mallory',40,'1729969372'),('110101198411164376','Lindsey',39,'(247)989-2111x256'),('110101198502083115','Cameron',67,'881-408-4736x2532'),('110101198603093949','Jared',39,'001-975-440-0365x55372'),('110101198610116271','Chris',22,'6369459526'),('110101198610289070','Shirley',50,'(132)996-0514'),('110101198709081849','Joshua',50,'643.108.8938'),('110101198810243608','Sarah',31,'+1-009-486-7233x49762'),('110101198908196586','Sherry',22,'(957)088-6953'),('110101198908252802','Adam',70,'001-674-825-7096'),('110101198909015468','Jamie',62,'(032)027-5531x1870'),('110101198910026821','Cindy',68,'057.053.6953x57258'),('110101199001011234','Zhangsan',30,'13800138000'),('110101199002022345','Lisi',28,'13900139000'),('110101199103086642','James',46,'428.095.5648'),('110101199407095228','Henry',51,'(484)693-2230x43443'),('110101199407142760','Angela',30,'191-603-1317'),('110101199506209367','Matthew',34,'339.628.9836x7628'),('110101199602114217','Hayley',44,'309-454-1411x140'),('110101199606058320','Cory',65,'199-279-8019x342'),('110101199611172474','Crystal',38,'(884)917-4311x866'),('110101199805127060','Brandon',56,'+1-306-591-1181x8776'),('110101199806024063','Dorothy',52,'815.165.9534x0806'),('110101199806092967','Spencer',69,'001-214-217-8565x2501'),('110101199806282974','Erin',63,'997-946-5506x277'),('110101200001019999','测试用户',25,'13900000000');
/*!40000 ALTER TABLE `passenger` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = gbk */ ;
/*!50003 SET character_set_results = gbk */ ;
/*!50003 SET collation_connection  = gbk_chinese_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `after_passenger_insert` AFTER INSERT ON `passenger` FOR EACH ROW -- 对于每一行受影响的记录都执行一次触发器体
BEGIN
    -- NEW 伪行（pseudo-row）包含了新插入的记录的数据
    INSERT INTO TriggerLog (table_name, operation, item_id, description)
    VALUES (
        'Passenger',
        'INSERT',
        NEW.id_card, -- 新记录的身份证号作为项目ID
        CONCAT('New passenger inserted. ID: ', NEW.id_card, ', Name: ', NEW.passname, ', Age: ', NEW.age)
    );
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = gbk */ ;
/*!50003 SET character_set_results = gbk */ ;
/*!50003 SET collation_connection  = gbk_chinese_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `after_passenger_update` AFTER UPDATE ON `passenger` FOR EACH ROW BEGIN
    -- OLD 伪行包含更新前的记录数据，NEW 伪行包含更新后的记录数据
    INSERT INTO TriggerLog (table_name, operation, item_id, description)
    VALUES (
        'Passenger',
        'UPDATE',
        NEW.id_card, -- 更新后记录的身份证号作为项目ID
        CONCAT('Passenger updated. ID: ', OLD.id_card, '. Name from "', OLD.passname, '" updated to "', NEW.passname, '". Phone from "', OLD.phone, '" updated to "', NEW.phone, '"')
    );
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = gbk */ ;
/*!50003 SET character_set_results = gbk */ ;
/*!50003 SET collation_connection  = gbk_chinese_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `after_passenger_delete` AFTER DELETE ON `passenger` FOR EACH ROW BEGIN
    -- OLD 伪行包含了被删除的记录的数据
    INSERT INTO TriggerLog (table_name, operation, item_id, description)
    VALUES (
        'Passenger', 
        'DELETE',
        OLD.id_card, -- 被删除记录的身份证号作为项目ID
        CONCAT('Passenger deleted. ID: ', OLD.id_card, ', Name: ', OLD.passname)
    );
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary view structure for view `passfeturefli`
--

DROP TABLE IF EXISTS `passfeturefli`;
/*!50001 DROP VIEW IF EXISTS `passfeturefli`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `passfeturefli` AS SELECT 
 1 AS `id_card`,
 1 AS `passname`,
 1 AS `flight_number`,
 1 AS `departure_time`,
 1 AS `arrival_time`,
 1 AS `airline_name`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary view structure for view `passhistoryfli`
--

DROP TABLE IF EXISTS `passhistoryfli`;
/*!50001 DROP VIEW IF EXISTS `passhistoryfli`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `passhistoryfli` AS SELECT 
 1 AS `id_card`,
 1 AS `passname`,
 1 AS `flight_number`,
 1 AS `departure_time`,
 1 AS `arrival_time`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ticket`
--

DROP TABLE IF EXISTS `ticket`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ticket` (
  `ticket_id` int NOT NULL AUTO_INCREMENT,
  `flight_number` varchar(20) NOT NULL,
  `id_card` varchar(20) NOT NULL,
  `seat_number` varchar(10) NOT NULL,
  `gate` varchar(10) DEFAULT NULL,
  `boarding_time` datetime NOT NULL,
  `cabin_seat` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`ticket_id`),
  KEY `flight_number` (`flight_number`),
  KEY `id_card` (`id_card`),
  CONSTRAINT `ticket_ibfk_1` FOREIGN KEY (`flight_number`) REFERENCES `flight` (`flight_number`),
  CONSTRAINT `ticket_ibfk_2` FOREIGN KEY (`id_card`) REFERENCES `passenger` (`id_card`)
) ENGINE=InnoDB AUTO_INCREMENT=53 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ticket`
--

LOCK TABLES `ticket` WRITE;
/*!40000 ALTER TABLE `ticket` DISABLE KEYS */;
INSERT INTO `ticket` VALUES (1,'CA1234','110101199001011234','12A','B12','2024-04-10 07:20:00','Y'),(2,'MU5678','110101199002022345','14C','A05','2024-04-10 08:30:00','C'),(3,'CA7836','110101199407142760','3F','B13','2024-04-28 11:46:59','Y'),(4,'MU4241','110101199806092967','2C','B28','2024-04-15 03:26:08','C'),(5,'CA1112','110101196009264879','30D','B24','2024-04-25 17:33:04','C'),(6,'CA1112','110101199103086642','8A','B5','2024-04-29 17:36:59','Y'),(7,'MU7290','110101196205083417','10A','A27','2024-04-29 10:56:40','C'),(8,'MU7290','110101199407095228','1C','A6','2024-04-20 18:22:32','C'),(9,'MU4241','110101199611172474','13C','C15','2024-04-15 23:55:33','C'),(10,'CA7836','110101198909015468','17D','C2','2024-04-26 11:41:57','Y'),(11,'CA1112','110101197011228296','5F','B14','2024-04-26 05:45:58','C'),(12,'MU4241','110101199103086642','19B','C13','2024-04-24 06:29:21','C'),(13,'CA7836','110101197906032146','4C','B21','2024-04-23 07:49:12','Y'),(14,'MU7290','110101198208177794','20B','C10','2024-04-21 12:08:45','Y'),(15,'MU7290','110101198910026821','20B','B4','2024-04-26 07:59:27','C'),(16,'CA2849','110101199806282974','1F','B28','2024-04-27 05:31:05','C'),(17,'MU7290','110101199805127060','9B','C30','2024-04-12 00:24:55','C'),(18,'CA1112','110101198312118306','12B','C21','2024-04-12 12:29:16','C'),(19,'CA2849','110101198306273248','20F','B11','2024-04-12 11:08:15','Y'),(20,'MU7290','110101198908252802','9E','A7','2024-04-21 10:10:46','C'),(21,'MU4241','110101198306273248','4F','A24','2024-04-22 21:02:35','Y'),(22,'CA7836','110101197507058250','16B','A13','2024-04-17 02:08:10','C'),(23,'CA1112','110101199806092967','1A','B23','2024-04-18 17:23:48','C'),(24,'CA1112','110101198909015468','16F','A2','2024-04-20 02:26:14','C'),(25,'CA7836','110101196206102759','2C','A4','2024-04-12 08:41:52','C'),(26,'CA7836','110101198603093949','6E','C10','2024-04-29 01:20:59','C'),(27,'MU4241','110101198208177794','13A','C12','2024-04-25 01:15:01','C'),(28,'CA2849','110101198810243608','26B','C17','2024-04-22 20:20:07','Y'),(29,'MU7290','110101199103086642','7C','A2','2024-04-15 11:04:23','Y'),(30,'CA2849','110101197702183195','24D','A17','2024-04-11 18:00:56','C'),(31,'MU4241','110101198908196586','15B','B2','2024-04-24 13:25:27','Y'),(32,'CA1112','110101198908252802','1F','C25','2024-04-17 17:40:28','C'),(33,'CA7836','110101195710268104','11A','A10','2024-04-12 19:29:07','C'),(34,'CA1112','110101199506209367','22A','B21','2024-04-27 22:30:49','Y'),(35,'MU4241','110101195510198228','8F','C13','2024-04-17 21:28:13','Y'),(36,'MU4241','110101199407095228','22A','A25','2024-04-23 10:59:58','C'),(37,'CA1112','110101199506209367','20A','B12','2024-04-21 21:50:40','C'),(38,'CA1112','110101198909015468','5B','A18','2024-04-20 15:38:31','Y'),(39,'CA7836','110101198709081849','22F','C19','2024-04-27 12:42:38','Y'),(40,'CA1112','110101197705159207','1A','B27','2024-04-13 22:37:34','C'),(41,'MU7290','110101199805127060','8B','A8','2024-04-21 13:03:14','Y'),(42,'MU4241','110101198908196586','12C','A22','2024-04-17 05:43:10','C'),(43,'MU7290','110101199606058320','20B','B26','2024-04-13 07:47:17','C'),(44,'MU7290','110101196010073093','9F','A9','2024-04-26 20:11:42','Y'),(45,'CA1112','110101199611172474','3C','A27','2024-04-20 06:01:11','C'),(46,'MU7290','110101199407095228','22B','B29','2024-04-22 12:01:14','C'),(47,'MU7290','110101196009264879','5B','C23','2024-04-11 05:16:14','Y'),(48,'CA2849','110101198610116271','1B','A26','2024-04-16 13:25:09','C'),(49,'CA1112','110101197212145297','22E','B21','2024-04-28 00:08:57','C'),(50,'MU7290','110101199407095228','15A','C27','2024-04-21 18:20:24','Y'),(51,'MU4241','110101195010215457','15C','A17','2024-04-12 13:45:30','Y'),(52,'MU4241','110101197705159207','7B','A3','2024-04-20 11:05:10','Y');
/*!40000 ALTER TABLE `ticket` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `triggerlog`
--

DROP TABLE IF EXISTS `triggerlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `triggerlog` (
  `log_id` int NOT NULL AUTO_INCREMENT,
  `table_name` varchar(50) NOT NULL,
  `operation` varchar(10) NOT NULL,
  `item_id` varchar(50) DEFAULT NULL,
  `description` text,
  `log_time` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`log_id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `triggerlog`
--

LOCK TABLES `triggerlog` WRITE;
/*!40000 ALTER TABLE `triggerlog` DISABLE KEYS */;
INSERT INTO `triggerlog` VALUES (1,'Passenger','INSERT','110101200001019999','New passenger inserted. ID: 110101200001019999, Name: 测试用户, Age: 25','2025-05-25 19:50:37'),(2,'Passenger','UPDATE','110101200001019999','Passenger updated. ID: 110101200001019999. Name from \"测试用户\" updated to \"测试用户\". Phone from \"13812345678\" updated to \"13900000000\"','2025-05-25 19:50:37'),(3,'Passenger','INSERT','110101200001018888','New passenger inserted. ID: 110101200001018888, Name: 待删除用户, Age: 30','2025-05-25 20:04:42'),(4,'Passenger','UPDATE','110101200001019999','Passenger updated. ID: 110101200001019999. Name from \"测试用户\" updated to \"测试用户\". Phone from \"13900000000\" updated to \"13900000000\"','2025-05-25 20:04:42'),(5,'Passenger','DELETE','110101200001018888','Passenger deleted. ID: 110101200001018888, Name: 待删除用户','2025-05-25 20:04:42'),(6,'Passenger','INSERT','51010119950101123X','New passenger inserted. ID: 51010119950101123X, Name: Wangping, Age: 28','2025-05-25 20:09:14'),(7,'Passenger','UPDATE','51010119950101123X','Passenger updated. ID: 51010119950101123X. Name from \"Wangping\" updated to \"Wangping\". Phone from \"13912345678\" updated to \"13887654321\"','2025-05-25 20:09:14'),(8,'Passenger','DELETE','51010119950101123X','Passenger deleted. ID: 51010119950101123X, Name: Wangping','2025-05-25 20:09:14'),(9,'Passenger','INSERT','110101200001018888','New passenger inserted. ID: 110101200001018888, Name: 待删除用户, Age: 30','2025-05-29 10:54:41'),(10,'Passenger','UPDATE','110101200001019999','Passenger updated. ID: 110101200001019999. Name from \"测试用户\" updated to \"测试用户\". Phone from \"13900000000\" updated to \"13900000000\"','2025-05-29 10:54:41'),(11,'Passenger','DELETE','110101200001018888','Passenger deleted. ID: 110101200001018888, Name: 待删除用户','2025-05-29 10:54:41');
/*!40000 ALTER TABLE `triggerlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `userinfo`
--

DROP TABLE IF EXISTS `userinfo`;
/*!50001 DROP VIEW IF EXISTS `userinfo`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `userinfo` AS SELECT 
 1 AS `id_card`,
 1 AS `passname`,
 1 AS `age`,
 1 AS `phone`*/;
SET character_set_client = @saved_cs_client;

--
-- Final view structure for view `airlineflicount`
--

/*!50001 DROP VIEW IF EXISTS `airlineflicount`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = gbk */;
/*!50001 SET character_set_results     = gbk */;
/*!50001 SET collation_connection      = gbk_chinese_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `airlineflicount` AS select `flight`.`airline_code` AS `airline_code`,count(0) AS `flight_count` from `flight` group by `flight`.`airline_code` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `flightsum`
--

/*!50001 DROP VIEW IF EXISTS `flightsum`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = gbk */;
/*!50001 SET character_set_results     = gbk */;
/*!50001 SET collation_connection      = gbk_chinese_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `flightsum` AS select `flight`.`flight_number` AS `flight_number`,`flight`.`departure_time` AS `departure_time`,`flight`.`arrival_time` AS `arrival_time`,(select `airport`.`airport_code` from `airport` where (`airport`.`airport_code` = `flight`.`departure_airport`)) AS `departure_airport_name`,(select `airport`.`city` from `airport` where (`airport`.`airport_code` = `flight`.`departure_airport`)) AS `departure_city`,(select `airport`.`airport_code` from `airport` where (`airport`.`airport_code` = `flight`.`arrival_airport`)) AS `arrival_airport_name`,(select `airport`.`city` from `airport` where (`airport`.`airport_code` = `flight`.`arrival_airport`)) AS `arrival_city` from `flight` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `flighttime`
--

/*!50001 DROP VIEW IF EXISTS `flighttime`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = gbk */;
/*!50001 SET character_set_results     = gbk */;
/*!50001 SET collation_connection      = gbk_chinese_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `flighttime` AS select `flight`.`flight_number` AS `flight_number`,`flight`.`departure_time` AS `departure_time`,`flight`.`arrival_time` AS `arrival_time`,timestampdiff(MINUTE,`flight`.`departure_time`,`flight`.`arrival_time`) AS `flight_time` from `flight` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `passfeturefli`
--

/*!50001 DROP VIEW IF EXISTS `passfeturefli`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = gbk */;
/*!50001 SET character_set_results     = gbk */;
/*!50001 SET collation_connection      = gbk_chinese_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `passfeturefli` AS select `passenger`.`id_card` AS `id_card`,`passenger`.`passname` AS `passname`,(select `ticket`.`flight_number` from `ticket` where (`ticket`.`id_card` = `passenger`.`id_card`)) AS `flight_number`,(select `flight`.`departure_time` from `flight` where ((`flight`.`flight_number` = (select `ticket`.`flight_number` from `ticket` where (`ticket`.`id_card` = `passenger`.`id_card`))) and (`flight`.`departure_time` > now()))) AS `departure_time`,(select `flight`.`arrival_time` from `flight` where ((`flight`.`flight_number` = (select `ticket`.`flight_number` from `ticket` where (`ticket`.`id_card` = `passenger`.`id_card`))) and (`flight`.`departure_time` > now()))) AS `arrival_time`,(select `airline`.`airline_name` from `airline` where (`airline`.`airline_code` = (select `flight`.`airline_code` from `flight` where (`flight`.`flight_number` = (select `ticket`.`flight_number` from `ticket` where (`ticket`.`id_card` = `passenger`.`id_card`)))))) AS `airline_name` from `passenger` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `passhistoryfli`
--

/*!50001 DROP VIEW IF EXISTS `passhistoryfli`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = gbk */;
/*!50001 SET character_set_results     = gbk */;
/*!50001 SET collation_connection      = gbk_chinese_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `passhistoryfli` AS select `passenger`.`id_card` AS `id_card`,`passenger`.`passname` AS `passname`,(select `ticket`.`flight_number` from `ticket` where (`ticket`.`id_card` = `passenger`.`id_card`)) AS `flight_number`,(select `flight`.`departure_time` from `flight` where ((`flight`.`flight_number` = (select `ticket`.`flight_number` from `ticket` where (`ticket`.`id_card` = `passenger`.`id_card`))) and (`flight`.`departure_time` <= now()))) AS `departure_time`,(select `flight`.`arrival_time` from `flight` where ((`flight`.`flight_number` = (select `ticket`.`flight_number` from `ticket` where (`ticket`.`id_card` = `passenger`.`id_card`))) and (`flight`.`departure_time` <= now()))) AS `arrival_time` from `passenger` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `userinfo`
--

/*!50001 DROP VIEW IF EXISTS `userinfo`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = gbk */;
/*!50001 SET character_set_results     = gbk */;
/*!50001 SET collation_connection      = gbk_chinese_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `userinfo` AS select `passenger`.`id_card` AS `id_card`,`passenger`.`passname` AS `passname`,`passenger`.`age` AS `age`,`passenger`.`phone` AS `phone` from `passenger` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-06-03 19:36:13
