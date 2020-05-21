// Fill in empty functions and defintions

#include "pintos_headers.h"

/*
freeSeats/count : a shared variable between bus and passenger

*/

struct station {
    struct lock* lock;
    struct condition* cond;
    // struct lock *lock = malloc(sizeof(struct lock));
    // struct condition *cond = malloc(sizeof(struct cond));
    int waitingPassengersCount;
    int freeSeats;
};

void station_setup(struct station *station) {
    station = malloc(sizeof(station));
    // struct station* station = {->waitingPassengersCount}
    lock_init(station->lock);
    cond_init(station->cond);
}

void bus_load_passengers(struct station *station, int count) {
    //count: number of total seats 
    station->freeSeats = count;
    
    // int freeSeats = station->freeSeats;
    // int waitingPassengersCount = station->waitingPassengersCount;
    
    lock_acquire(station->lock);
    cond_broadcast(station->cond, station->lock);
    while (station->freeSeats > 0 || station->waitingPassengersCount > 0)       
    {
        cond_wait(station->cond, station->lock);
        
    }
    // while (station->freeSeats > 0 || station->waitingPassengersCount > 0)       
    // {
    //     cond_wait(station->cond, station->lock);
        
    // }
    lock_release(station->lock);
    
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


        
        

    // } while (station->freeSeats > 0 || station->waitingPassengersCount > 0);
    
    // lock_release(lock);
    
    // int temp = count;
    // lock = lock_init();
    // do
    // {

    //     lock_acquire();


    //     lock_release();
    // } while (true);
    
}

void passenger_waitfor_bus(struct station *station) {
    
    // int freeSeats = station->freeSeats;
    // int waitingPassengersCount = station->waitingPassengersCount;
    // waitingPassengersCount--;
    // station->waitingPassengersCount = waitingPassengersCount;
    lock_acquire(station->lock);
    while (station->waitingPassengersCount > 0)
    {
        // lock_acquire(station->lock);
        
    }
    station->waitingPassengersCount--;
    cond_signal(station->cond, station->lock);
    lock_release(station->lock);
    
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
    lock_acquire(station->lock);
    while (station->freeSeats > 0)
    {
        cond_wait(station->cond, station->lock);
    }
    station->freeSeats--;
    cond_signal(station->cond, station->lock);
    lock_release(station->lock);
    
    


}
