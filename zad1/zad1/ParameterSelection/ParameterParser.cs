﻿using GeneticSharp.Domain.Crossovers;
using GeneticSharp.Domain.Mutations;
using GeneticSharp.Domain.Selections;
using GeneticSharp.Domain.Terminations;
using System;

namespace zad1.selection
{
    class ParameterParser
    {
        public static ISelection ParseSelection(int n, object x = null, object y = null)
        {
            switch (n)
            {
                case 1:
                    return new EliteSelection();
                case 2:
                    return new RouletteWheelSelection();
                case 3:
                    return new StochasticUniversalSamplingSelection();
                case 4:
                    if (x is int)
                        if (y is bool)
                            return new TournamentSelection((int)x, (bool)y);
                        else
                            return new TournamentSelection((int)x);
                    else
                        return new TournamentSelection();
                default:
                    throw new ArgumentException();
            }
        }

        public static ICrossover ParserCrossover(int n, object x = null)
        {
            switch (n)
            {
                case 1:
                    if (x is float)
                        return new UniformCrossover((float)x);
                    else
                        return new UniformCrossover();
                case 2:
                    if (x is int)
                        return new OnePointCrossover((int)x);
                    else
                        return new OnePointCrossover();
                case 3:
                    return new ThreeParentCrossover();
                default:
                    throw new ArgumentException();
            }
        }

        public static IMutation ParseMutation(int n)
        {
            switch (n)
            {
                case 1:
                    return new FlipBitMutation();
                case 2:
                    return new ReverseSequenceMutation();
                case 3:
                    return new TworsMutation();
                case 4:
                    return CustomUniformMutation.Create();
                default:
                    throw new ArgumentException();
            }
        }

        public static ITermination ParseTermination(int n, object x = null)
        {
            switch (n)
            {
                case 1:
                    if (x is int)
                        return new FitnessStagnationTermination((int)x);
                    else
                        return new FitnessStagnationTermination();
                case 2:
                    if (x is int)
                        return new GenerationNumberTermination((int)x);
                    else
                        return new GenerationNumberTermination();
                case 3:
                    if (x is TimeSpan)
                        return new TimeEvolvingTermination((TimeSpan)x);
                    else
                        return new TimeEvolvingTermination();
                default:
                    throw new ArgumentException();
            }
        }
    }
}
