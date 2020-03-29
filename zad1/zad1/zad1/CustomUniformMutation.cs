using GeneticSharp.Domain.Crossovers;
using GeneticSharp.Domain.Mutations;
using GeneticSharp.Domain.Randomizations;
using System;
using System.Collections.Generic;
using System.Text;

namespace zad1
{
    public class CustomUniformMutation : UniformMutation
    {
        int[] MutableGenesIndexes { get; set; }

        private CustomUniformMutation(int[] mutableGenesIndexes) : base(mutableGenesIndexes) 
        {
            MutableGenesIndexes = mutableGenesIndexes;
        }

        public CustomUniformMutation GenerateAdaptedMutation()
        {
            for(int i=0; i < MutableGenesIndexes.Length; i++)
            {
                if(MutableGenesIndexes[i] == 1)
                {
                    MutableGenesIndexes[i] = 0;
                    break;
                }
            }

            return new CustomUniformMutation(MutableGenesIndexes);
        }


        public static CustomUniformMutation Create(int numberOfBits)
        {
            int[] mutableGenesIndexes = RandomizationProvider.Current.GetInts(numberOfBits, 0, 1);
            return new CustomUniformMutation(mutableGenesIndexes);
        }
    }
}
