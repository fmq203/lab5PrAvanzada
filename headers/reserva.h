#ifndef RESERVA_H
#define RESERVA_H

#include "consulta.h"

class Reserva: public Consulta
{
private:
    Fecha fechaReserva;
public:
    Reserva();
    Reserva(Fecha f, Hora h, Usuario* soc, Usuario* med, Fecha fechaRes);

    Fecha getFechaReserva();

    void setFechaReserva(Fecha f);

    ~Reserva();
};

#endif