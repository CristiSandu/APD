package com.apd.tema2.factory;

import com.apd.tema2.Main;
import com.apd.tema2.entities.*;
import com.apd.tema2.intersections.*;
import com.apd.tema2.utils.Constants;

import java.util.concurrent.Executor;
import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

/**
 * Clasa Factory ce returneaza implementari ale InterfaceHandler sub forma unor
 * clase anonime.
 */
public class IntersectionHandlerFactory {

    public static IntersectionHandler getHandler(String handlerType) {
        // simple semaphore intersection
        // max random N cars roundabout (s time to exit each of them)
        // roundabout with exactly one car from each lane simultaneously
        // roundabout with exactly X cars from each lane simultaneously
        // roundabout with at most X cars from each lane simultaneously
        // entering a road without any priority
        // crosswalk activated on at least a number of people (s time to finish all of
        // them)
        // road in maintenance - 2 ways 1 lane each, X cars at a time
        // road in maintenance - 1 way, M out of N lanes are blocked, X cars at a time
        // railroad blockage for s seconds for all the cars
        // unmarked intersection
        // cars racing
        return switch (handlerType) {
            case "simple_semaphore" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    String start  = "Car " + car.getId() + " has reached the semaphore, now waiting...";
                    System.out.println(start);
                    try {
                        sleep(car.getWaitingTime());
                    }catch (Exception ex)
                    {
                    }

                    String end = "Car " + car.getId() + " has waited enough, now driving...";
                    System.out.println(end);
                }
            };
            case "simple_n_roundabout" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {

                }
            };
            case "simple_strict_1_car_roundabout" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    String start  = "Car " + car.getId() + " has reached the roundabout, now waiting...";
                    System.out.println(start);
                    IntersectionC2 inter =  (IntersectionC2)Main.intersection;
                    try {
                        inter.getSemaphor().acquire();
                    }catch (InterruptedException exc)
                    {

                    }
                    String middel  = "Car " + car.getId() + " has entered the roundabout";
                    System.out.println(middel);

                    synchronized (this) {
                        try{
                            sleep(inter.getTime());
                        }catch (Exception ex) {
                        }
                        inter.getSemaphor().release();
                        String end  = "Car " + car.getId() + " has exited the roundabout after " + inter.getTime() / 1000 + " seconds";
                        System.out.println(end);

                    }
                }
            };
            case "simple_strict_x_car_roundabout" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {

                }
            };
            case "simple_max_x_car_roundabout" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    // Get your Intersection instance

                    try {
                        sleep(car.getWaitingTime());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } // NU MODIFICATI

                    // Continuati de aici
                }
            };
            case "priority_intersection" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    // Get your Intersection instance

                    try {
                        sleep(car.getWaitingTime());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } // NU MODIFICATI

                    // Continuati de aici
                }
            };
            case "crosswalk" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    
                }
            };
            case "simple_maintenance" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    
                }
            };
            case "complex_maintenance" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    
                }
            };
            case "railroad" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    
                }
            };
            default -> null;
        };
    }
}
