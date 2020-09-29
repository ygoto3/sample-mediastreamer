package overlay

class OverlayUsecase(val overlayRepository: IOverlayRepository) {

  def FindOverlay(overlayId: OverlayId): Option[Overlay] = {
    overlayRepository.Find(overlayId)
  }

  def RegisterOverlay(overlay: Overlay): Either[String, Int] = {
    overlayRepository.Update(overlay)
  }

}
