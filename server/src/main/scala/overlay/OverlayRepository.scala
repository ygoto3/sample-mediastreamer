package overlay

import framework.database.RepositoryBase
import slick.jdbc.MySQLProfile.api._
import slick.lifted.ProvenShape

import scala.concurrent.Await
import scala.concurrent.duration.DurationInt

class OverlayRepository extends RepositoryBase with IOverlayRepository {

  val overlayTableQuery = TableQuery[OverlaysTable]

  override def Find(overlayId: OverlayId): Option[Overlay] = {
    val q = overlayTableQuery.filter(_.Id === overlayId.Value).map(_.Text)
    var res: Option[Overlay] = None
    try {
      res = (for {
        text <- Await.result(db.run(q.result), 5.seconds)
      } yield Overlay(overlayId, OverlayText(text))).headOption
    } catch {
      case e => println(e)
    } finally {
      db.close()
    }
    res
  }

  override def Update(overlay: Overlay): Either[String, Int] = {
    val q = for { o <- overlayTableQuery if o.Id === overlay.Id.Value } yield o.Text
    val action = q.update(overlay.Text.Value)
    var res: Either[String, Int] = Left("No overlay found")
    try {
      val affectedRow = Await.result(db.run(action), 5.seconds)
      res = Right(affectedRow)
    } catch {
      case e => println(e)
    } finally {
      db.close()
    }
    res
  }
}

class OverlaysTable(tag: Tag) extends Table[(Long, String)](tag, "overlays") {
  def Id = column[Long]("id", O.PrimaryKey)
  def Text = column[String]("text")
  def * : ProvenShape[(Long, String)] = (Id, Text)
}