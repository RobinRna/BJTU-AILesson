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
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-06-03 19:35:57
