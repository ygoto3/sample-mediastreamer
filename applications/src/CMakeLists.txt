target_sources(receiver
  PRIVATE
    receiver.cpp
)

target_sources(sender
  PRIVATE
    sender.cpp
)

target_sources(registrar
  PRIVATE
    registrar.cpp
)

add_subdirectory(ReceiverApp)
add_subdirectory(SenderApp)
add_subdirectory(RegistrarApp)
add_subdirectory(Overlay)
add_subdirectory(framework)

