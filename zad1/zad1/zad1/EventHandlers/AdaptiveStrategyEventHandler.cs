using GeneticSharp.Domain;
using GeneticSharp.Domain.Crossovers;
using System;
using zad1.selection;

namespace zad1.EventHandlers
{
    class AdaptiveStrategyEventHandler : IEventHandler
    {
        private double previouslyBestFitness = 0.0;

        public void Handle(object sender, EventArgs e)
        {
            var geneticAlgorithm = sender as GeneticAlgorithm;

            var bestFitness = geneticAlgorithm.BestChromosome.Fitness.Value;

            var epsilon = Math.Abs(0.9 * bestFitness);
            if (Math.Abs(bestFitness - previouslyBestFitness) < epsilon)
            {
                if (geneticAlgorithm.Crossover is UniformCrossover)
                {
                    var mixProbability = (geneticAlgorithm.Crossover as UniformCrossover).MixProbability;
                    geneticAlgorithm.Crossover = ParameterParser.ParserCrossover(1, (float)(0.9 * mixProbability));
                }

                if (geneticAlgorithm.Mutation is CustomUniformMutation)
                {
                    geneticAlgorithm.Mutation = (geneticAlgorithm.Mutation as CustomUniformMutation).GenerateAdaptedMutation();
                }
            }

            previouslyBestFitness = bestFitness;
        }
    }
}
