-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: localhost    Database: socket_chat_db
-- ------------------------------------------------------
-- Server version	5.7.17-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `chat_activity`
--

DROP TABLE IF EXISTS `chat_activity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chat_activity` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `date_in` datetime NOT NULL,
  `date_out` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`),
  KEY `user_id` (`user_id`),
  CONSTRAINT `chat_activity_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `chat_users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=32 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chat_activity`
--

LOCK TABLES `chat_activity` WRITE;
/*!40000 ALTER TABLE `chat_activity` DISABLE KEYS */;
INSERT INTO `chat_activity` VALUES (1,4,'2017-01-12 22:00:00','2017-01-13 22:00:00'),(2,4,'2017-01-13 21:49:49','2017-01-13 22:28:21'),(3,4,'2017-01-13 21:51:50','2017-01-13 22:28:21'),(4,4,'2017-01-13 21:54:18','2017-01-13 22:28:21'),(5,4,'2017-01-13 22:25:02','2017-01-13 22:28:21'),(6,4,'2017-01-13 22:28:16','2017-01-13 22:28:21'),(7,4,'2017-01-13 22:58:54','2017-01-13 22:58:59'),(8,10,'2017-01-13 23:01:53','2017-01-13 23:02:47'),(9,10,'2017-01-13 23:24:06','2017-01-13 23:24:23'),(10,10,'2017-01-13 23:29:30','2017-01-13 23:29:38'),(11,4,'2017-01-13 23:46:51','0000-00-00 00:00:00'),(12,10,'2017-01-13 23:47:05','0000-00-00 00:00:00'),(13,13,'2017-01-13 23:54:47','2017-01-13 23:58:44'),(14,4,'2017-01-13 23:56:26','0000-00-00 00:00:00'),(15,4,'2017-01-14 00:15:58','2017-01-14 00:16:21'),(16,10,'2017-01-14 00:16:13','0000-00-00 00:00:00'),(17,4,'2017-01-14 00:17:54','2017-01-14 00:19:06'),(18,10,'2017-01-14 00:18:27','0000-00-00 00:00:00'),(19,10,'2017-01-14 00:32:58','2017-01-14 00:33:46'),(20,4,'2017-01-14 00:33:36','2017-01-14 00:34:58'),(21,10,'2017-01-14 00:34:06','2017-01-14 00:34:53'),(22,4,'2017-01-14 00:35:15','2017-01-14 00:35:27'),(23,13,'2017-01-14 00:36:57','2017-01-14 00:37:53'),(24,10,'2017-01-14 00:37:15','0000-00-00 00:00:00'),(25,4,'2017-01-14 00:37:33','0000-00-00 00:00:00'),(26,13,'2017-01-14 00:38:18','0000-00-00 00:00:00'),(27,13,'2017-01-14 00:46:46','0000-00-00 00:00:00'),(28,13,'2017-01-14 00:50:13','0000-00-00 00:00:00'),(29,13,'2017-01-14 00:52:12','2017-01-14 00:52:32'),(30,4,'2017-01-14 01:36:31','2017-01-14 01:36:36'),(31,4,'2017-01-14 01:48:16','2017-01-14 01:48:19');
/*!40000 ALTER TABLE `chat_activity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `chat_messages`
--

DROP TABLE IF EXISTS `chat_messages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chat_messages` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `date` datetime NOT NULL,
  `message` varchar(1054) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `user_id` (`user_id`),
  CONSTRAINT `chat_messages_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `chat_users` (`id`),
  CONSTRAINT `chat_messages_ibfk_2` FOREIGN KEY (`user_id`) REFERENCES `chat_users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chat_messages`
--

LOCK TABLES `chat_messages` WRITE;
/*!40000 ALTER TABLE `chat_messages` DISABLE KEYS */;
INSERT INTO `chat_messages` VALUES (1,4,'2017-01-13 22:25:46','hello'),(2,4,'2017-01-13 22:28:18','killo'),(3,4,'2017-01-13 22:58:57','hello'),(4,10,'2017-01-13 23:02:24','kilo'),(5,10,'2017-01-13 23:24:23','hoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo'),(6,10,'2017-01-13 23:29:36','kilololas'),(7,4,'2017-01-13 23:56:49','jukikikik'),(8,10,'2017-01-14 00:33:40','sdf'),(9,4,'2017-01-14 00:34:12','dfdfdfd'),(10,4,'2017-01-14 00:37:58','sdsdsdsd'),(11,4,'2017-01-14 01:36:34','fffdfkjgjd'),(12,4,'2017-01-14 01:48:17','g');
/*!40000 ALTER TABLE `chat_messages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `chat_users`
--

DROP TABLE IF EXISTS `chat_users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chat_users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` varchar(256) NOT NULL,
  `password` varchar(256) NOT NULL,
  `date` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `loginIndex` (`login`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chat_users`
--

LOCK TABLES `chat_users` WRITE;
/*!40000 ALTER TABLE `chat_users` DISABLE KEYS */;
INSERT INTO `chat_users` VALUES (1,'Anna','password','2017-01-08 22:39:05'),(2,'Alina','password','2017-01-09 00:18:29'),(3,'Akella','password','2017-01-09 00:41:43'),(4,'Akilla','password','2017-01-09 00:41:43'),(5,'Akolla','password','2017-01-09 00:41:43'),(6,'Adik','password','2017-01-09 01:06:20'),(7,'Alla','password','2017-01-09 00:19:25'),(10,'Layla','password','2017-01-13 23:01:39'),(13,'Stepan','password','2017-01-13 23:54:47');
/*!40000 ALTER TABLE `chat_users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-01-14  4:44:11
