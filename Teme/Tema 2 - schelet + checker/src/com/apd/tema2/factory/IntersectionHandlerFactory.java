package com.apd.tema2.factory;

import com.apd.tema2.Main;
import com.apd.tema2.entities.*;
import com.apd.tema2.intersections.*;
import com.apd.tema2.utils.Constants;

import java.util.Vector;
import java.util.concurrent.BrokenBarrierException;
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
                    //formez mesajul initial
                    String start = "Car " + car.getId() + " has reached the semaphore, now waiting...";
                    System.out.println(start); //printez mesajul initial
                    try {
                        sleep(car.getWaitingTime()); //sleep cat nr de secunde cat au masina
                    } catch (Exception ex) {
                    }

                    String end = "Car " + car.getId() + " has waited enough, now driving..."; // formare mesaj final
                    System.out.println(end); // printare mesaj final
                }
            };
            case "simple_n_roundabout" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    IntersectionC2 inter = (IntersectionC2) Main.intersection;// returnare intersectia
                    String start = "Car " + car.getId() + " has reached the roundabout, now waiting...";// formare mesaj de intrare
                    System.out.println(start);// afisare mesaj de intrare in rotunda

                    try {
                        inter.getSemaphor().acquire();   // daca nu mai e loc in giratoriu asteapta
                    } catch (InterruptedException ex) {
                    }

                    String middel = "Car " + car.getId() + " has entered the roundabout"; // formare mesaj de intrare
                    System.out.println(middel); // printare mesaj

                    try {
                        sleep(inter.getTime()); // timp de asteptare in giratoriu
                    } catch (Exception ex) {
                    }

                    // formare mesaj de iesire
                    String end = "Car " + car.getId() + " has exited the roundabout after " + inter.getTime() / 1000 + " seconds";
                    System.out.println(end);// printare mesaj de iesire

                    inter.getSemaphor().release();// anuntam ca mai e un loc liber in giratoriu
                }
            };
            case "simple_strict_1_car_roundabout" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    IntersectionC3 inter = (IntersectionC3) Main.intersection; //instantere intersectie
                    Vector<Semaphore> semS = inter.getSemaphors();  // instantire vector de semafoare

                    String start = "Car " + car.getId() + " has reached the roundabout"; //formare mesa de intrare in sens
                    System.out.println(start); // printare mesaj de intrare

                    try {
                        semS.get(car.getPriority()).acquire(); //verific daca este loc pe sensul de mers al masinii
                    } catch (InterruptedException exc) {

                    }

                    // formez mesaj de intrare
                    String middel = "Car " + car.getId() + " has entered the roundabout from lane " + car.getPriority();
                    System.out.println(middel); // printez mesaj de intrare

                    try {
                        sleep(inter.getTime()); // astept 2 timpul T in giratoriu
                    } catch (Exception ex) {
                    }
                    // formez mesaj de iesire giratoriu
                    String end = "Car " + car.getId() + " has exited the roundabout after " + inter.getTime() / 1000 + " seconds";
                    System.out.println(end); // printare mesaj de iesire

                    semS.get(car.getPriority()).release(); // eliberez locul din giratoriu de pe sens lui car
                }
            };
            case "simple_strict_x_car_roundabout" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    IntersectionC4 inter = (IntersectionC4) Main.intersection; //instantere intersectie
                    Vector<Semaphore> semS = inter.getSemaphors();//instantere vector de semafoare

                    // formare mesaj de intrare
                    String start = "Car " + car.getId() + " has reached the roundabout, now waiting...";
                    System.out.println(start); // prinatre mesaj

                    try {
                        inter.getCyclicBarr().await();          //punere bariera ca sa sincronizez toate masinile a intrarea in rotunda
                    } catch (InterruptedException | BrokenBarrierException e) {
                        e.printStackTrace();
                    }

                    try {
                        semS.get(car.getStartDirection()).acquire(); //verific daca este loc pe sensul de mers al masinii
                    } catch (InterruptedException exc) {

                    }
                    //daca da continui daca nu astept pana se face loc

                    // formez mesajul selectie
                    String middel1 = "Car " + car.getId() + " was selected to enter the roundabout from lane "
                            + car.getStartDirection();
                    System.out.println(middel1); // printez mesajul
                    try {
                        inter.getCyclicBarr2().await();    // sincronizez thredurile care urmeaza sa intre in rotunda
                    } catch (InterruptedException | BrokenBarrierException e) {
                        e.printStackTrace();
                    }

                    // formez mesajul de intrare in rotunda
                    String middel2 = "Car " + car.getId() + " has entered the roundabout from lane " + car.getStartDirection();
                    System.out.println(middel2); // afisez mesajul de intrare
                    try {
                        inter.getCyclicBarr2().await();     // sincronizez thredurile din rotund
                    } catch (InterruptedException | BrokenBarrierException e) {
                        e.printStackTrace();
                    }


                    try {
                        sleep(inter.getTime()); // astept timpul T in rotunda
                    } catch (Exception ex) {
                    }

                    // formse mesajul de iesire
                    String end = "Car " + car.getId() + " has exited the roundabout after " + inter.getTime() / 1000 + " seconds";
                    System.out.println(end); // afisez mesajul de iesire

                    try {
                        inter.getCyclicBarr2().await();   // sincronizez thredurile din rotunda pentru iesire
                    } catch (InterruptedException | BrokenBarrierException e) {
                        e.printStackTrace();
                    }

                    semS.get(car.getStartDirection()).release();// eliberez locul din giratoriu de pe sens lui car
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

                    IntersectionC4 inter = (IntersectionC4) Main.intersection;
                    Vector<Semaphore> semS = inter.getSemaphors();

                    // formare mesaj de inceput
                    String start = "Car " + car.getId() + " has reached the roundabout from lane " + car.getStartDirection();
                    System.out.println(start); // printare mesaj de inceput

                    try {
                        inter.getCyclicBarr().await(); // sincronizez toate thredurile sa intre in acleasi timp in rotunda
                    } catch (InterruptedException | BrokenBarrierException e) {
                        e.printStackTrace();
                    }

                    try {
                        semS.get(car.getStartDirection()).acquire();  // daca nu este loc asteapta pana se face
                    } catch (InterruptedException exc) {

                    }

                    // formare mesaj de intrare
                    String middel2 = "Car " + car.getId() + " has entered the roundabout from lane " + car.getStartDirection();
                    System.out.println(middel2); // afisare mesaj de intrare

                    try {
                        sleep(inter.getTime()); // asteptare T sec pentru ca iesi din giratoriu
                    } catch (Exception ex) {
                    }

                    // formare mesaj de iesire
                    String end = "Car " + car.getId() + " has exited the roundabout after " + inter.getTime() / 1000 + " seconds";
                    System.out.println(end);// afisare mesaj de iesire

                    semS.get(car.getStartDirection()).release(); // eliberare loc in giratoriu
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
                    IntersectionC6 inter = (IntersectionC6) Main.intersection;
                    inter.ProirInter(car);
                }
            };
            case "crosswalk" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    //Formare mesaje
                    String green = "Car " + car.getId() + " has now green light";
                    String red = "Car " + car.getId() + " has now red light";
                    IntersectionC7 inter = (IntersectionC7) Main.intersection;
                    inter.setLastElem(0);
                    //cat timp nu au terminat de trecut pietoni
                    System.out.println(green);
                    while (!Main.pedestrians.isFinished()) {
                        if (Main.pedestrians.isPass() && inter.getLastElem() == 0) {  // daca sunt in trecere
                                System.out.println(red); // afisam mesajul ca sa pus semaforul
                                inter.setLastElem(1); // si schimbam culoarea
                            //}
                        } else if (inter.getLastElem() == 1 && !Main.pedestrians.isPass()) { // altfel daca nu trec
                             // vreificam daca culoarea nu este verde
                                System.out.println(green);// daca da afisam mesajul de green
                                inter.setLastElem(0); // si schimbam culoarea salvata
                        }
                    }
                }
            };
            case "simple_maintenance" -> new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    // formare mesaje
                    String start = "Car " + car.getId() + " from side number " + car.getStartDirection() + " has reached the bottleneck";
                    String end = "Car " + car.getId() + " from side number " + car.getStartDirection() + " has passed the bottleneck";

                    System.out.println(start);// afisare primul mesaj
                    IntersectionC8 inter = (IntersectionC8) Main.intersection;

                    if (car.getStartDirection() == 0) {  // daca are directia 0
                        try {
                            inter.getSemaphor1().acquire();  // daca este loc continuam
                        } catch (InterruptedException ex) {
                        }

                        try {
                            inter.getBar(inter.getCurentPass()).await(); //asteptam  sa aliniem toate masinile
                        } catch (InterruptedException | BrokenBarrierException ex2) {
                        }

                        // si le scoatem pe rand
                        System.out.println(end);
                        inter.getSemaphor2().release(); // dand release la semaforul de pe celalat sens de mers

                    } else if (car.getStartDirection() == 1) { // daca au sensul 1
                        try {
                            inter.getSemaphor2().acquire();  // daca avem loc continuam
                        } catch (InterruptedException ex) {
                        }

                        try {
                            inter.getBar(inter.getCurentPass()).await(); //asteptam  sa aliniem toate masinile
                        } catch (InterruptedException | BrokenBarrierException ex2) {
                        }

                        // si le scoatem pe rand
                        System.out.println(end);
                        inter.getSemaphor1().release();// dand release la semaforul de pe celalat sens de mers
                    }
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
                    //Formare mesaje
                    String start = "Car " + car.getId() + " from side number " + car.getStartDirection() + " has stopped by the railroad";
                    String middle = "The train has passed, cars can now proceed";
                    String end = "Car " + car.getId() + " from side number " + car.getStartDirection() + " has started driving";
                    //printare mesaj de inceput
                    System.out.println(start);
                    IntersectionC10 inter = (IntersectionC10) Main.intersection;

                    //daca avem sensul 0 punem in coada 1
                    if (car.getStartDirection() == 0) {
                        inter.setQueue1(car);
                    } else if (car.getStartDirection() == 1) {// daca avem sensul 1 punem in coada 2
                        inter.setQueue2(car);
                    }

                    try {
                        inter.getBar().await();// punem bariera pana trece trenul
                    } catch (InterruptedException | BrokenBarrierException ex2) {

                    }
                    if (car.getId() == 0) { // dupa ce a trecut pe un singur thred
                        int max;
                        System.out.println(middle); // afisam mesajul de trecere

                        // si golesc stivele afisand masinile care ies
                        while (inter.getQueue1().size() != 0) {
                            Car care = inter.getQueue1().poll();
                            String end1 = "Car " + care.getId() + " from side number " + care.getStartDirection() + " has started driving";
                            System.out.println(end1);
                        }
                        while (inter.getQueue2().size() != 0) {
                            Car car1 = inter.getQueue2().poll();
                            String end2 = "Car " + car1.getId() + " from side number " + car1.getStartDirection() + " has started driving";
                            System.out.println(end2);
                        }
                    }
                }
            };
            default -> null;
        };
    }
}
