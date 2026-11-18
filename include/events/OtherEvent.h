#ifndef OTHER_EVENT_H
#define OTHER_EVENT_H

#include "events/Event.h"

class OtherEvent : public Event {
private:
    std::string customType;

public:
    OtherEvent(int eventId, const std::string& name, const std::string& description,
               const std::string& clubName, const std::string& date, const std::string& time,
               const std::string& venue, double fee, int totalSeats, const std::string& customType,
               int seatsLeft = -1, const std::string& status = "PENDING");

    std::string getCustomType() const;
    nlohmann::json toJson() const override;
    void displayDetails() const override;
    std::string generateCertificate(const std::string& studentName) const override;

    static std::shared_ptr<OtherEvent> fromJson(const nlohmann::json& j);
};

#endif
