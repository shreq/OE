using GeneticSharp.Domain;
using GeneticSharp.Domain.Chromosomes;
using System;
using System.Collections.Generic;
using System.Text;

namespace zad1.EventHandlers
{
    public class ConsoleLogEventHandler : IEventHandler
    {
        public string[] FunctionValues { get; private set; }

        private double latestFitness;

        public ConsoleLogEventHandler(string[] functionValues)
        {
            FunctionValues = functionValues;
        }

        public void Handle(object sender, EventArgs e)
        {
            var geneticAlgorithm = sender as GeneticAlgorithm;
            var bestChromosome = geneticAlgorithm.BestChromosome as FloatingPointChromosome;
            var bestFitness = bestChromosome.Fitness.Value;

            if (bestFitness != latestFitness)
            {
                latestFitness = bestFitness;
                var phenotype = bestChromosome.ToFloatingPoints();

                var coords = "\nParameters:";
                for (int i = 0; i < FunctionValues.Length; i++)
                {
                    coords += "\n" + FunctionValues[i] + " = " + phenotype[i];
                }

                Console.WriteLine(
                    "\n[Generation " + geneticAlgorithm.GenerationsNumber + "] \nBest fitness = " + bestFitness + coords
                );
            }
        }
    }
}
