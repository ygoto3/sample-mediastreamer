#include <cpprest/http_client.h>
#include "Overlay/Overlay.hpp"
#include "Overlay/OverlayRepository.hpp"

namespace overlay {

using namespace web;
using namespace web::http;
using namespace web::http::client;

std::future<overlay::Overlay> OverlayRepository::Get(overlay::OverlayId id) {
    return std::async(std::launch::async, [id] {
        int id_;
        utility::string_t text;
        try {
            pplx::create_task([id] {
                std::string url{"http://localhost:8080/v1/overlays/"};
                overlay::OverlayId overlayId = id;
                url.append(std::to_string(overlayId.getValue()));
                http_client client(url);
                return client.request(methods::GET);
            }).then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                }
            }).then([&](json::value json) {
                id_ = json["id"].as_integer();
                text = json["text"].as_string();
            }).get();
            return overlay::Overlay(overlay::OverlayId(id), overlay::OverlayText(text));
        } catch (std::exception e) {
            std::cerr << "Failed to fetch an overlay data: " << e.what() << std::endl;
        }
    });
}

std::future<int> OverlayRepository::Update(overlay::Overlay overlay) {
    return std::async(std::launch::async, [overlay] {
        try {
            return pplx::create_task([overlay] {
                overlay::Overlay o = (overlay::Overlay)overlay;

                std::string url{"http://localhost:8080/v1/overlays/"};
                url.append(std::to_string(o.getId().getValue()));
                http_client client(url);

                http_request request(methods::PUT);
                request.headers().add("Content-Type", "application/json");

                std::string body{"{\"text\": \""};
                body.append(o.getText().getValue());
                body.append("\"}");
                request.set_body(body);

                return client.request(request);
            }).then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return 0;
                }
                return 1;
            }).get();
        } catch (std::exception e) {
            std::cerr << e.what() << ": Failed to update an overlay data." << std::endl;
        }
    });
}

}
