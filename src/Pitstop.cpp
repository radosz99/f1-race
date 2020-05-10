#include"Pitstop.hpp"
#include"PitstopState.hpp"

//TODO: add engineer thread with skill atribute and others needed
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
        case PitstopState::WAITING_FOR_BOLIDE:
            return "WAITING_FOR_BOLIDE";
    }
}
