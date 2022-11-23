-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1:3306
-- Tiempo de generación: 22-11-2022 a las 13:36:56
-- Versión del servidor: 5.7.36
-- Versión de PHP: 7.4.26

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `restaurante_tg`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `pedidos`
--

DROP TABLE IF EXISTS `pedidos`;
CREATE TABLE IF NOT EXISTS `pedidos` (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `estado` varchar(255) NOT NULL,
  `mesa` varchar(255) NOT NULL,
  `orden` json NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `pedidos`
--

INSERT INTO `pedidos` (`id`, `estado`, `mesa`, `orden`) VALUES
(1, 'TERMINADO', 'H', '{\"bebida\": \"Agua\", \"alimento\": \"Sushi\"}'),
(2, 'TERMINADO', 'H', '{\"bebida\": \"Cerveza\", \"alimento\": \"Salchipapas\"}'),
(3, 'TERMINADO', 'H', '{\"bebida\": \"Jugo\", \"alimento\": \"Perro\"}'),
(4, 'TERMINADO', 'G', '{\"bebida\": \"Cerveza\", \"alimento\": \"Hamburguesa\"}'),
(5, 'TERMINADO', 'G', '{\"bebida\": \"Jugo\", \"alimento\": \"Sushi\"}'),
(6, 'TERMINADO', 'G', '{\"bebida\": \"Jugo\", \"alimento\": \"Perro\"}'),
(7, 'TERMINADO', 'H', '{\"bebida\": \"Soda\", \"alimento\": \"Hamburguesa\"}'),
(8, 'TERMINADO', 'H', '{\"bebida\": \"Agua\", \"alimento\": \"Salchipapas\"}'),
(9, 'TERMINADO', 'H', '{\"bebida\": \"Jugo\", \"alimento\": \"Hamburguesa\"}'),
(10, 'TERMINADO', 'G', '{\"bebida\": \"Cerveza\", \"alimento\": \"Hamburguesa\"}'),
(11, 'TERMINADO', 'G', '{\"bebida\": \"Jugo\", \"alimento\": \"Hamburguesa\"}'),
(14, 'TERMINADO', 'E', '{\"bebida\": \"Jugo\", \"alimento\": \"Pizza\"}'),
(15, 'TERMINADO', 'E', '{\"bebida\": \"Gaseosa\", \"alimento\": \"Pizza\"}'),
(16, 'TERMINADO', 'E', '{\"bebida\": \"Gaseosa\", \"alimento\": \"Pizza\"}'),
(17, 'TERMINADO', 'E', '{\"bebida\": \"Cerveza\", \"alimento\": \"Hamburguesa\"}'),
(18, 'TERMINADO', 'E', '{\"bebida\": \"Cerveza\", \"alimento\": \"Perro\"}'),
(19, 'TERMINADO', 'E', '{\"bebida\": \"Jugo\", \"alimento\": \"Hamburguesa\"}'),
(20, 'TERMINADO', 'G', '{\"bebida\": \"Soda\", \"alimento\": \"Hamburguesa\"}'),
(21, 'TERMINADO', 'G', '{\"bebida\": \"Agua\", \"alimento\": \"Hamburguesa\"}'),
(22, 'TERMINADO', 'E', '{\"bebida\": \"Jugo\", \"alimento\": \"Pizza\"}'),
(23, 'TERMINADO', 'E', '{\"bebida\": \"Agua\", \"alimento\": \"Hamburguesa\"}'),
(24, 'TERMINADO', 'F', '{\"bebida\": \"Jugo\", \"alimento\": \"Hamburguesa\"}'),
(25, 'TERMINADO', 'F', '{\"bebida\": \"Soda\", \"alimento\": \"Perro\"}'),
(26, 'TERMINADO', 'D', '{\"bebida\": \"Soda\", \"alimento\": \"Sushi\"}'),
(27, 'TERMINADO', 'D', '{\"bebida\": \"Cerveza\", \"alimento\": \"Salchipapas\"}'),
(28, 'TERMINADO', 'F', '{\"bebida\": \"Jugo\", \"alimento\": \"Hamburguesa\"}');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `productos`
--

DROP TABLE IF EXISTS `productos`;
CREATE TABLE IF NOT EXISTS `productos` (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `producto` varchar(255) NOT NULL,
  `precio` int(255) NOT NULL,
  `tipo` int(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `productos`
--

INSERT INTO `productos` (`id`, `producto`, `precio`, `tipo`) VALUES
(1, 'Pizza', 15000, 0),
(2, 'Hamburguesa', 18000, 0),
(3, 'Perro', 12000, 0),
(4, 'Salchipapas', 13000, 0),
(5, 'Sushi', 20000, 0),
(6, 'Gaseosa', 3000, 1),
(7, 'Jugo', 5000, 1),
(8, 'Soda', 5500, 1),
(9, 'Cerveza', 6500, 1),
(10, 'Agua', 2500, 1);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
