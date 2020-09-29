import akka.actor.ActorSystem
import akka.http.scaladsl.Http
import akka.stream.ActorMaterializer
import framework.network.Routes

import scala.concurrent.ExecutionContextExecutor
import scala.io.StdIn

object App extends App with Routes {
  implicit val system: ActorSystem = ActorSystem()
  implicit val materializer = ActorMaterializer()
  implicit val dispatcher: ExecutionContextExecutor = system.dispatcher

  val bindingFuture = Http().bindAndHandle(routes, "localhost", 8080)

  println(s"Server online at http://localhost:8080\nPress RETURN to stop...")
  StdIn.readLine()
  bindingFuture
    .flatMap(_.unbind())
    .onComplete(_ => system.terminate())
}
