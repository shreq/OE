using GeneticSharp.Domain.Crossovers;
using GeneticSharp.Domain.Mutations;
using GeneticSharp.Domain.Selections;
using GeneticSharp.Domain.Terminations;
using System;
using System.Collections.Generic;
using System.Text;

namespace zad1.selection
{
    public class ParameterSelection
    {
        public string[] Variables { get; set; }
        public string Expression { get; set; }
        public float LowerBound { get; set; }
        public float UpperBound { get; set; }
        public bool AdaptiveOn {get; set; }
        public ISelection Selection { get; set; }
        public ICrossover Crossover { get; set; }
        public IMutation Mutation { get; set; }
        public ITermination Termination { get; set; }
    }
}
