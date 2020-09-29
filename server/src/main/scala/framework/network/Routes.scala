package framework.network

import akka.http.scaladsl.marshallers.sprayjson.SprayJsonSupport
import akka.http.scaladsl.model.{HttpResponse, StatusCodes}
import akka.http.scaladsl.server.Directives._
import overlay._
import spray.json.DefaultJsonProtocol

import scala.concurrent.ExecutionContextExecutor

case class OverlayFormat(id: Long, text: String)
case class OverlayRequestFormat(text: String)

trait Routes extends DefaultJsonProtocol with SprayJsonSupport {
  implicit val dispatcher: ExecutionContextExecutor
  implicit val overlayFormat = jsonFormat2(OverlayFormat)
  implicit val overlayRequestFormat = jsonFormat1(OverlayRequestFormat)

  val routes = pathPrefix("v1") {
    pathPrefix("overlays") {
      path(IntNumber) { id =>
        get {
          val overlayUsecase = new OverlayUsecase(new OverlayRepository)
          complete {
            overlayUsecase.FindOverlay(OverlayId(id)) match {
              case Some(_overlay) => OverlayFormat(id, _overlay.Text.Value)
              case None => HttpResponse(StatusCodes.NotFound)
            }
          }
        } ~
        put {
          entity(as[OverlayRequestFormat]) { o =>
            val overlayUsecase = new OverlayUsecase(new OverlayRepository)
            val overlay = Overlay(OverlayId(id), OverlayText(o.text))
            complete {
              overlayUsecase.RegisterOverlay(overlay) match {
                case Left(errorMessage) => HttpResponse(
                  StatusCodes.InternalServerError, entity = errorMessage)
                case Right(i) if i > 0 => OverlayFormat(id, o.text)
                case Right(_) => HttpResponse(
                  StatusCodes.InternalServerError, entity = "No overlay was registered.")
              }
            }
          }
        }
      }
    }
  }

}
