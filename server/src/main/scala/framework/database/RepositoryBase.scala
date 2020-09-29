package framework.database

import slick.jdbc.MySQLProfile.api._

trait RepositoryBase {
  val db = Database.forURL("jdbc:mysql://localhost/sample_mediastreamer", "root", "mysql", driver = "com.mysql.cj.jdbc.Driver")
}
