#include"Pitstop.hpp"
#include"PitstopState.hpp"

Pitstop::Pitstop(int id) : id(id)
{

}
PitstopState Pitstop::getStatus() const
{
    return status;
}

void Pitstop::setStatus(PitstopState newStatus)
{
    status = newStatus;
}

int Pitstop::getId() const
{
    return id;
}

std::string Pitstop::getStateString() const
{
    switch (status)
    {
        case PitstopState::FREE:
            return "FREE";
        case PitstopState::BUSY:
            return "BUSY";
        case PitstopState::WAITING_FOR_BOLID:
            return "WAITING_FOR_BOLID";
    }
}
