// Fill in empty functions and defintions

#include "pintos_headers.h"

/*
freeSeats/count : a shared variable between bus and passenger

*/

struct station {
    // struct lock* lock;
    // struct condition* busAvailable;
    // struct condition* freeSeatAvailable;
    // struct condition* passengerAvailable;
    // struct condition* passengerOnBus;
    // struct condition* passengerLoaded;
    struct lock lock;
    struct condition busAvailable;
    struct condition freeSeatAvailable;
    struct condition passengerAvailable;
    struct condition passengerOnBus;
    struct condition passengerLoaded;
    // struct lock *lock = malloc(sizeof(struct lock));
    // struct condition *cond = malloc(sizeof(struct cond));
    int waitingPassengersCount;
    int freeSeats;
};

void station_setup(struct station *station) {
    station = malloc(sizeof(station));
    station->freeSeats = 0;
    station->waitingPassengersCount = 0;
    // struct station* station = {->waitingPassengersCount}
    // struct lock* lock = &(station->lock);
    
    // struct condition* busAvailable = &(station->busAvailable);
    // struct condition* freeSeatAvailable = &(station->freeSeatAvailable);
    // struct condition* passengerAvailable = &(station->passengerAvailable);
    // struct condition* passengerOnBus = &(station->passengerOnBus);
    // struct condition* passengerLoaded = &(station->passengerLoaded);

    lock_init(&(station->lock));
    cond_init(&(station->busAvailable));
    cond_init(&(station->freeSeatAvailable));
    cond_init(&(station->passengerAvailable));
    cond_init(&(station->passengerOnBus));
    cond_init(&(station->passengerLoaded));
    // lock_init(station->lock);
    // cond_init(station->busAvailable);
    // cond_init(station->freeSeatAvailable);
    // cond_init(station->passengerAvailable);
    // cond_init(station->passengerOnBus);
}

void bus_load_passengers(struct station *station, int count) {
    //count: number of total seats 
    lock_init(&(station->lock));
    cond_init(&(station->busAvailable));
    cond_init(&(station->freeSeatAvailable));
    cond_init(&(station->passengerAvailable));
    cond_init(&(station->passengerOnBus));
    cond_init(&(station->passengerLoaded));

    station->freeSeats = count;
    
    // int freeSeats = station->freeSeats;
    // int waitingPassengersCount = station->waitingPassengersCount;
    
    lock_acquire(&(station->lock));
    cond_broadcast(&(station->busAvailable), &(station->lock));
    while (station->freeSeats > 0 || station->waitingPassengersCount > 0)       
    {
        cond_wait(&(station->passengerAvailable),&(station->lock));
        // cond_wait(&(station->passengerOnBus), &(station->lock));
        cond_wait(&(station->passengerLoaded), &(station->lock));
    }
    
    // while (station->freeSeats > 0 || station->waitingPassengersCount > 0)       
    // {
    //     cond_wait(station->cond, station->lock);
        
    // }
    lock_release(&(station->lock));
    
    // do
    // {   
    //     cond_wait(station->cond, station->lock);
    //     if (station->freeSeats >= station->waitingPassengersCount)
    //     {
    //         station->freeSeats -= station->waitingPassengersCount;
    //         // freeSeats -= waitingPassengersCount;
    //         // count = freeSeats;
    //         // waitingPassengersCount = 0;
    //         // station->passengersCount = 0;
    //     }



    
}

void passenger_waitfor_bus(struct station *station) {
    lock_init(&(station->lock));
    cond_init(&(station->busAvailable));
    cond_init(&(station->freeSeatAvailable));
    cond_init(&(station->passengerAvailable));
    cond_init(&(station->passengerOnBus));
    cond_init(&(station->passengerLoaded));

    lock_acquire(&(station->lock));
    station->waitingPassengersCount++;
    cond_signal(&(station->passengerAvailable), &(station->lock));
    while (station->freeSeats == 0)
    {   
        // cond_wait(&(station->busAvailable), &(station->lock));
        cond_wait(&(station->freeSeatAvailable), &(station->lock));
    }
    station->waitingPassengersCount--;
    cond_signal(&(station->passengerLoaded), &(station->lock));
    lock_release(&(station->lock));
    //signal no passenger!
    
    


    // int freeSeats = station->freeSeats;
    // int waitingPassengersCount = station->waitingPassengersCount;
    // waitingPassengersCount--;
    // station->waitingPassengersCount = waitingPassengersCount;
    
    // lock_acquire(station->lock);
    // while (station->waitingPassengersCount > 0)
    // {
    //     lock_acquire(station->lock);
        
    // }
    // station->waitingPassengersCount--;
    // cond_signal(station->cond, station->lock);
    // lock_release(station->lock);
    
    // lock_acquire(station->lock);
    // station->waitingPassengersCount += 1;
    // if (station->freeSeats > 0) {    
    //     station->waitingPassengersCount -= 1;
    // }
    // cond_signal(station->cond, station->lock);
    // lock_release(station->lock);
    
}

void passenger_on_board(struct station *station) {
    // station->passengersCount = station->passengersCount - 1;
    // freeSeats--;
    lock_init(&(station->lock));
    cond_init(&(station->busAvailable));
    cond_init(&(station->freeSeatAvailable));
    cond_init(&(station->passengerAvailable));
    cond_init(&(station->passengerOnBus));
    cond_init(&(station->passengerLoaded));

    lock_acquire(&(station->lock));
    // while (station->freeSeats == 0)
    // {
    //     cond_wait(station->freeSeatAvailable, station->lock);
    // }
    station->freeSeats--;
    cond_signal(&(station->passengerOnBus),&(station->lock));
    lock_release(&(station->lock));
    
    


}
