#pragma once

namespace DarkMagic
{
    inline FVector2D ClipSpaceToNormalizedDeviceCoords(const FVector4& ClipSpaceCoords)
    {
        const float HomogenousDivisor = 1.0f / ClipSpaceCoords.W;
        return FVector2D(ClipSpaceCoords.X * HomogenousDivisor, ClipSpaceCoords.Y * HomogenousDivisor);
    }

    inline FVector2D NormalizedDeviceCoordsToScreenSpace(const FVector2D& NormalizedDeviceCoords, const FVector2D& ScreenSize)
    {
        // Source: https://stackoverflow.com/questions/8491247/c-opengl-convert-world-coords-to-screen2d-coords
        FVector2D Result;
        Result.X = (NormalizedDeviceCoords.X + 1.0f) / 2.0f * ScreenSize.X;
        Result.Y = (NormalizedDeviceCoords.Y + 1.0f) / 2.0f * ScreenSize.Y;
        return Result;
    }

    inline FVector4 WorldSpaceToClipSpace(const FVector& WorldSpacePosition, const FMatrix& ViewProjectionMatrix)
    {
        return ViewProjectionMatrix.TransformFVector4(FVector4(WorldSpacePosition.X, WorldSpacePosition.Y, WorldSpacePosition.Z, 1.0f));
    }

    inline FVector2D WorldSpaceToScreenSpace(const FVector& WorldSpacePosition, const FMatrix& ViewProjectionMatrix, const FVector2D& ScreenSize)
    {
        const auto ClipSpace = WorldSpaceToClipSpace(WorldSpacePosition, ViewProjectionMatrix);
        const auto NormalizedDeviceCoords = ClipSpaceToNormalizedDeviceCoords(ClipSpace);
        return NormalizedDeviceCoordsToScreenSpace(NormalizedDeviceCoords, ScreenSize);
    }

    inline FVector2D ScreenSpaceToClipSpace(const FVector2D& ScreenSpacePosition, const FVector2D& ScreenSize)
    {
        // Convert to normalized texture coordinates
        const FVector2D TexCoord(ScreenSpacePosition.X / ScreenSize.X, ScreenSpacePosition.Y / ScreenSize.Y);

        // Convert to clip space
        return FVector2D(TexCoord.X * 2.0f - 1.0f, TexCoord.Y * 2.0f - 1.0f);
    }

    inline FVector ScreenSpaceToWorldSpace(const FVector2D& ScreenSpacePosition, const FVector2D& ScreenSize, const FMatrix& InverseProjectionMatrix, const FMatrix& InverseViewMatrix)
    {
        const FVector2D ClipSpace = ScreenSpaceToClipSpace(ScreenSpacePosition, ScreenSize);

        // TransformPosition
        const FVector ClipSpaceVector(ClipSpace.X, ClipSpace.Y, 1.0f);
        const FVector ViewSpace = InverseProjectionMatrix.TransformPosition(ClipSpaceVector);
        const FVector WorldSpace = InverseViewMatrix.TransformPosition(ViewSpace);
        
        return WorldSpace;
    }
}