// Fill out your copyright notice in the Description page of Project Settings.

#include "TouchReceiveComponent.h"

UTouchReceiveComponent::UTouchReceiveComponent(const FObjectInitializer &ObjectInitializer)
    : UBoxComponent(ObjectInitializer)
{
    SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
    SetGenerateOverlapEvents(true);
    SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}