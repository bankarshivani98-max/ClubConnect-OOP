#include "events/OtherEvent.h"
#include <iostream>
#include <sstream>

OtherEvent::OtherEvent(int eventId, const std::string& name, const std::string& description,
                       const std::string& clubName, const std::string& date, const std::string& time,
                       const std::string& venue, double fee, int totalSeats, const std::string& customType,
                       int seatsLeft, const std::string& status)
    : Event(eventId, name, description, clubName, date, time, venue, fee, totalSeats, seatsLeft, status),
      customType(customType) {}

std::string OtherEvent::getCustomType() const {
    return customType;
}

nlohmann::json OtherEvent::toJson() const {
    return {
        {"eventId", eventId},
        {"type", "Other"},
        {"customType", customType},
        {"name", name},
        {"description", description},
        {"clubName", clubName},
        {"date", date},
        {"time", time},
        {"venue", venue},
        {"fee", fee},
        {"totalSeats", totalSeats},
        {"seatsLeft", getSeatsLeft()},
        {"status", status}
    };
}

void OtherEvent::displayDetails() const {
    std::cout << "[OTHER EVENT] " << name << " | Type: " << customType << "\n"
              << "  Club: " << clubName << " | Date: " << date << " " << time
              << " | Venue: " << venue << " | Seats Left: " << getSeatsLeft() << "/" << totalSeats
              << " | Fee: INR " << fee << "\n"
              << "  Description: " << description << "\n";
}

std::string OtherEvent::generateCertificate(const std::string& studentName) const {
    std::ostringstream oss;
    oss << "========================================================\n"
        << "           CERTIFICATE OF PARTICIPATION                 \n"
        << "========================================================\n"
        << "This certifies that:\n\n"
        << "                " << studentName << "\n\n"
        << "has participated in the " << customType << " event:\n"
        << "       \"" << name << "\"\n"
        << "organized by " << clubName << " on " << date << " at " << venue << ".\n"
        << "========================================================\n";
    return oss.str();
}

std::shared_ptr<OtherEvent> OtherEvent::fromJson(const nlohmann::json& j) {
    int id = j.value("eventId", 0);
    std::string name = j.value("name", "");
    std::string description = j.value("description", "");
    std::string club = j.value("clubName", "");
    std::string date = j.value("date", "");
    std::string time = j.value("time", "");
    std::string venue = j.value("venue", "");
    double fee = j.value("fee", 0.0);
    int totalSeats = j.value("totalSeats", 0);
    int seatsLeft = j.value("seatsLeft", totalSeats);
    std::string status = j.value("status", "PENDING");
    std::string customType = j.value("customType", "");

    return std::make_shared<OtherEvent>(id, name, description, club, date, time, venue, fee,
                                        totalSeats, customType, seatsLeft, status);
}
