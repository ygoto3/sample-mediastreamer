package overlay

trait IOverlayRepository {
  def Find(overlayId: OverlayId): Option[Overlay]
  def Update(overlay: Overlay): Either[String, Int]
}

