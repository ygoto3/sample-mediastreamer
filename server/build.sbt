name := "sample-mediastreamer-server"

version := "0.1"

scalaVersion := "2.13.3"

libraryDependencies ++= Seq(
  "com.typesafe.akka" %% "akka-http" % "10.2.0",
  "com.typesafe.akka" %% "akka-actor" % "2.6.8",
  "com.typesafe.akka" %% "akka-stream" % "2.6.8",
  "com.typesafe.akka" %% "akka-http-spray-json" % "10.2.0",
  "mysql" % "mysql-connector-java" % "8.0.11",
  "com.typesafe.slick" %% "slick" % "3.3.2",
  "org.slf4j" % "slf4j-log4j12" % "1.7.2"
)
